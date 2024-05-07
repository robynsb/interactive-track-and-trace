#include "LGlyphLayer.h"
#include "../commands/SpawnPointCallback.h"
#include <vtkActor2D.h>
#include <vtkGlyph2D.h>
#include <vtkLookupTable.h>
#include <vtkGlyphSource2D.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleUser.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>

#include "../CartographicTransformation.h"

vtkSmartPointer<SpawnPointCallback> LGlyphLayer::createSpawnPointCallback() {
  auto newPointCallBack = vtkSmartPointer<SpawnPointCallback>::New();
  newPointCallBack->setData(this->data);
  newPointCallBack->setPoints(this->points);
  newPointCallBack->setRen(this->ren);
  newPointCallBack->setUVGrid(this->uvGrid);
  newPointCallBack->setBeached(this->particlesBeached);
  return newPointCallBack;
}

// Further notes; current thinking is to allow tracking a particle's age by using a scalar array in the VtkPolyData. This would be incremented for every tick/updateData function call.

/** 
 * Build and returns a vtkLookupTable for the given number of colours in grayscale.
 * @param n : number of colours to add to the SetTableRange
 * @return : a vtkLookupTable with grayscale colours from [1,1,1,1] to [0.5,0.5,0.5,0.5] in n steps.
 */
vtkSmartPointer<vtkLookupTable> buildLut(int n) {
  vtkNew<vtkLookupTable> lut;
  lut->SetNumberOfColors(n);
  lut->SetTableRange(0, n-1);
  lut->SetScaleToLinear();
  lut->Build();
  for (int i=0; i < n; i++) {
    lut->SetTableValue(i, 1-(0.5*i/(n-1)), 1-(0.5*i/(n-1)), 1-(0.5*i/(n-1)),  1-(0.5*i/(n-1)));
  }
  // set the last value to separate fully beached particles from those that have simply not moved in a bit.
  lut->SetTableValue(n-1, 0, 0, 0, 0.25);
  return lut;
}

LGlyphLayer::LGlyphLayer(std::shared_ptr<UVGrid> uvGrid, std::unique_ptr<AdvectionKernel> advectionKernel) {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(2);

  this->points = vtkSmartPointer<vtkPoints>::New();
  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->data->SetPoints(this->points);

  this->particlesBeached = vtkSmartPointer<vtkIntArray>::New();
  this->particlesBeached->SetName("particlesBeached");
  this->particlesBeached->SetNumberOfComponents(0);

  this->data->GetPointData()->AddArray(this->particlesBeached);
  this->data->GetPointData()->SetActiveScalars("particlesBeached");

  advector = std::move(advectionKernel);
  this->uvGrid = uvGrid;

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter(uvGrid);
  transformFilter->SetInputData(data);

  vtkNew<vtkGlyphSource2D> circleSource;
  circleSource->SetGlyphTypeToCircle();
  circleSource->SetScale(0.02);
  circleSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(circleSource->GetOutputPort());
  glyph2D->SetInputConnection(transformFilter->GetOutputPort());
  glyph2D->SetScaleModeToDataScalingOff();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->SetLookupTable(buildLut(this->beachedAtNumberOfTimes));
  mapper->SetScalarRange(0, this->beachedAtNumberOfTimes);
  mapper->Update();
  
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  this->ren->AddActor(actor);
}


// creates a few points so we can test the updateData function
void LGlyphLayer::spoofPoints() {
    // auto id =this->points->InsertNextPoint(6.532949683882039, 53.24308582564463, 0); // Coordinates of Zernike
    // this->particlesBeached->SetValue(id, 0);
    // id = this->points->InsertNextPoint(5.315307819255385, 60.40001057122271, 0); // Coordinates of Bergen
    // this->particlesBeached->SetValue(id, 0);
    // id = this->points->InsertNextPoint( 6.646210231365825, 46.52346296009023, 0); // Coordinates of Lausanne
    // this->particlesBeached->SetValue(id, 0);
    // id = this->points->InsertNextPoint(-6.553894313570932, 62.39522131195857, 0); // Coordinates of the top of the Faroe islands
    // this->particlesBeached->SetValue(id, 0);

  for (int i=0; i < 330; i+=5) {
    for (int j=0; j < 330; j+=5) {
      this->points->InsertNextPoint(-15.875+(12.875+15.875)/330*j, 46.125+(62.625-46.125)/330*i, 0);
      this->particlesBeached->InsertNextValue(0);
    }
  }

  this->points->Modified();
}

void LGlyphLayer::updateData(int t) {
  const int SUPERSAMPLINGRATE = 4;
  double point[3], oldX, oldY;
  bool modifiedData = false;

  // iterate over every point.
  for (vtkIdType n=0; n < this->points->GetNumberOfPoints(); n++) {
    int beachedFor = this->particlesBeached->GetValue(n);
    // first check: only update non-beached particles.
    if (beachedFor < this->beachedAtNumberOfTimes) {
      this->points->GetPoint(n, point);
      // second check: only update points within our grid's boundary.
      if (point[0] <= this->uvGrid->lonMin() or point[0] >= this->uvGrid->lonMax() or point[1] <= this->uvGrid->latMin() or point[1] >= this->uvGrid->latMax()) {
        // sets any particle out of bounds to be beached - so it gets assigned the right colour in the lookup table.
        this->particlesBeached->SetValue(n, this->beachedAtNumberOfTimes);
        continue;
      }

      oldX = point[0]; oldY = point[1];

      // supersampling
      for (int i=0; i < SUPERSAMPLINGRATE; i++) {
        std::tie(point[1], point[0]) = advector->advect(t, point[1], point[0], (t-this->lastT)/SUPERSAMPLINGRATE);
      }

      // if the particle's location remains unchanged, increase beachedFor number. Else, decrease it and update point position.
      if (oldX == point[0] and oldY == point[1]) {
        this->particlesBeached->SetValue(n, beachedFor+1);
      } else {
        this->particlesBeached->SetValue(n, std::max(beachedFor-1, 0));
        this->points->SetPoint(n, point);
        modifiedData = true;
      }
    }
  }
  if (modifiedData) this->points->Modified();
  this->lastT = t;
}

void LGlyphLayer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  auto newPointCallBack = createSpawnPointCallback();
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::MouseMoveEvent, newPointCallBack);
}
