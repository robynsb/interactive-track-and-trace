#include "LGlyphLayer.h"
#include "../commands/SpawnPointCallback.h"
#include <vtkActor2D.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
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
  newPointCallBack->setData(data);
  newPointCallBack->setPoints(points);
  newPointCallBack->setRen(ren);
  newPointCallBack->setUVGrid(uvGrid);
  return newPointCallBack;
}

// Further notes; current thinking is to allow tracking a particle's age by using a scalar array in the VtkPolyData. This would be incremented for every tick/updateData function call.
// Another challenge is the concept of beaching; dead particles must not be included in the advect function call (wasted computations), but they should not be outright deleted from the vtkPoints either (we still want to display them). Working Solution: have another array of ints in the vtkPolyData, which tracks for how many calls of UpdateData a given particle has not had its position changed. If this int reaches some treshold (5? 10? 3? needs some testing), exclude the particle from the advect call.
//
// TODO: modelling all this in vtkClasses is workable, but ideally i would want to work with a native C++ class. See if this is doable and feasible.

LGlyphLayer::LGlyphLayer(std::shared_ptr<UVGrid> uvGrid, std::unique_ptr<AdvectionKernel> advectionKernel) {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(2);

  this->points = vtkSmartPointer<vtkPoints>::New();
  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->data->SetPoints(this->points);

  advector = std::move(advectionKernel);
  this->uvGrid = uvGrid;

  auto camera = createNormalisedCamera();
  ren->SetActiveCamera(camera);

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter(uvGrid);
  transformFilter->SetInputData(data);

  vtkNew<vtkGlyphSource2D> circleSource;
  circleSource->SetGlyphTypeToCircle();
  circleSource->SetScale(0.05);
  circleSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(circleSource->GetOutputPort());
  glyph2D->SetInputConnection(transformFilter->GetOutputPort());
  glyph2D->SetColorModeToColorByScalar();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  this->ren->AddActor(actor);
}

// creates a few points so we can test the updateData function
void LGlyphLayer::spoofPoints() {
  this->points->InsertNextPoint(-4.125, 61.375, 0);
  this->points->InsertNextPoint(6.532949683882039, 53.24308582564463, 0); // Coordinates of Zernike
  this->points->InsertNextPoint(5.315307819255385, 60.40001057122271, 0); // Coordinates of Bergen
  this->points->InsertNextPoint(6.646210231365825, 46.52346296009023, 0); // Coordinates of Lausanne
  this->points->InsertNextPoint(-6.553894313570932, 62.39522131195857,
                                0); // Coordinates of the top of the Faroe islands

  this->points->Modified();
}

void LGlyphLayer::updateData(int t) {
  const int SUPERSAMPLINGRATE = 4;
  double point[3];
  for (vtkIdType n = 0; n < this->points->GetNumberOfPoints(); n++) {
    this->points->GetPoint(n, point);
    for (int i = 0; i < SUPERSAMPLINGRATE; i++) {
      std::tie(point[1], point[0]) = advector->advect(t, point[1], point[0], (t-lastT)/SUPERSAMPLINGRATE);
    }
    this->points->SetPoint(n, point[0], point[1], 0);
  }
  lastT = t;
  this->points->Modified();
}

void LGlyphLayer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  auto newPointCallBack = createSpawnPointCallback();
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, newPointCallBack);
  interactor->AddObserver(vtkCommand::MouseMoveEvent, newPointCallBack);
}
