#include "LagrangeGlyphs.h"
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

vtkSmartPointer<SpawnPointCallback> LagrangeGlyphs::createSpawnPointCallback() {
  auto newPointCallBack = vtkSmartPointer<SpawnPointCallback>::New();
  newPointCallBack->setData(this->data);
  newPointCallBack->setPoints(this->points);
  newPointCallBack->setRen(this->ren);
  newPointCallBack->setUVGrid(this->uvGrid);
  newPointCallBack->setBeached(this->particlesBeached);
  return newPointCallBack;
}

/**
 * Build and returns a vtkLookupTable for the given number of colours in grayscale.
 * @param n : number of colours to add to the SetTableRange
 * @return : a vtkLookupTable with grayscale colours from [1,1,1,1] to [0.5,0.5,0.5,0.5] in n steps.
 */
vtkSmartPointer<vtkLookupTable> buildLut(int n) {
  vtkNew<vtkLookupTable> lut;
  lut->SetNumberOfColors(n);
  lut->SetTableRange(0, n - 1);
  lut->SetScaleToLinear();
  lut->Build();

  double lightColor[3] = {44/255, 61/255, 85/255}; // #2c3d55
  double blackColor[3] = {0.0, 0.0, 0.0}; // Black

  // Interpolate colors between light and black
  for (int i = 0; i < n; i++) {
    double t = static_cast<double>(i) / (n - 1); // Interpolation factor
    double color[3];
    for (int j = 0; j < 3; j++) {
      color[j] = (1.0 - t) * lightColor[j] + t * blackColor[j];
    }
    lut->SetTableValue(i, color[0], color[1], color[2], 1.0);
  }

  // Set the last value to fully black
  lut->SetTableValue(n - 1, blackColor[0], blackColor[1], blackColor[2], 1.0);

  return lut;
}

LagrangeGlyphs::LagrangeGlyphs(std::shared_ptr<UVGrid> uvGrid, std::unique_ptr<AdvectionKernel> advectionKernel) {
  this->points = vtkSmartPointer<vtkPoints>::New();
  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->data->SetPoints(this->points);

  this->particlesBeached = vtkSmartPointer<vtkIntArray>::New();
  this->particlesBeached->SetName("particlesBeached");
  this->particlesBeached->SetNumberOfComponents(0);

//  this->data->GetPointData()->AddArray(this->particlesBeached);
//  this->data->GetPointData()->SetActiveScalars("particlesBeached");

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
//  mapper->SetLookupTable(buildLut(this->beachedAtNumberOfTimes));
//  mapper->SetScalarRange(0, this->beachedAtNumberOfTimes);
  mapper->Update();
  
  actor->SetMapper(mapper);

  this->ren->AddActor(actor);
}

// creates a few points so we can test the updateData function
void LagrangeGlyphs::spoofPoints() {
  for (int i=0; i < 330; i+=5) {
    for (int j=0; j < 330; j+=5) {
      this->points->InsertNextPoint(-15.875+(12.875+15.875)/330*j, 46.125+(62.625-46.125)/330*i, 0);
      this->particlesBeached->InsertNextValue(0);
    }
  }

  this->points->Modified();
}

void LagrangeGlyphs::updateData(int t) {
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
        int dt = (t-this->lastT)/SUPERSAMPLINGRATE;
        if(dt < 0) {
          // TODO: This is a hack for when the t wraps around,
          // there is probably a more elegant way of dealing with this whole thing
          // that involves having two separate DTs.
          // One for the "render" step time, and one for the computation step time.
          dt = t;
        }
        std::tie(point[1], point[0]) = advector->advect(t, point[1], point[0], dt);
      }

      // if the particle's location remains unchanged, increase beachedFor number. Else, decrease it and update point position.
      if (abs(oldX - point[0]) < EPS and abs(oldY-point[1]) < EPS) {
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

void LagrangeGlyphs::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  auto newPointCallBack = createSpawnPointCallback();
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::MouseMoveEvent, newPointCallBack);
}

vtkSmartPointer<vtkPoints> LagrangeGlyphs::getPoints() {
  return points;
}

vtkSmartPointer<vtkIntArray> LagrangeGlyphs::getBeached() {
  return particlesBeached;
}

void LagrangeGlyphs::setColour(int red, int green, int blue) {
  actor->GetProperty()->SetColor(red/255.0, green/255.0, blue/255.0);
}