#include "SpawnPointCallback.h"

#include <vtkVertex.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>

#include "../CartographicTransformation.h"

void convertDisplayToWorld(vtkRenderer *renderer, int x, int y, double *worldPos) {
  double displayPos[3] = {static_cast<double>(x), static_cast<double>(y), 0.0};
  renderer->SetDisplayPoint(displayPos);
  renderer->DisplayToWorld();
  renderer->GetWorldPoint(worldPos);
}

void SpawnPointCallback::Execute(vtkObject *caller, unsigned long evId, void *callData) {
    // Note the use of reinterpret_cast to cast the caller to the expected type.
    auto interactor = reinterpret_cast<vtkRenderWindowInteractor *>(caller);

    if (evId == vtkCommand::LeftButtonPressEvent) {
        dragging = true;
    }
    if (evId == vtkCommand::LeftButtonReleaseEvent) {
        dragging = false;
    }
    if (!dragging) {
        return;
    }

    int x, y;
    interactor->GetEventPosition(x, y);

    double worldPos[4] = {2, 0 ,0, 0};
    double displayPos[3] = {static_cast<double>(x), static_cast<double>(y), 0.0};
    ren->SetDisplayPoint(displayPos);
    ren->DisplayToWorld();
    ren->GetWorldPoint(worldPos);
    inverseCartographicProjection->TransformPoint(worldPos, worldPos);

    points->InsertNextPoint(worldPos[0], worldPos[1], 0);
    this->particlesBeached->InsertNextValue(0);

    // FIXME:  The below lines cause some weird interaction with our vtkTimer.
    // see github issue  https://github.com/MakeNEnjoy/interactive-track-and-trace/issues/28
    this->particlesBeached->Modified();
    this->points->Modified();
    ren->GetRenderWindow()->Render();
}


SpawnPointCallback::SpawnPointCallback() : data(nullptr),
                                           points(nullptr),
                                           inverseCartographicProjection(nullptr),
                                           uvGrid(nullptr) { }

SpawnPointCallback *SpawnPointCallback::New() {
  return new SpawnPointCallback;
}

void SpawnPointCallback::setData(const vtkSmartPointer<vtkPolyData> &data) {
  this->data = data;
}

void SpawnPointCallback::setPoints(const vtkSmartPointer<vtkPoints> &points) {
  this->points = points;
}

void SpawnPointCallback::setRen(const vtkSmartPointer<vtkRenderer> &ren) {
  this->ren = ren;
}

void SpawnPointCallback::setUVGrid(const std::shared_ptr<UVGrid> &uvGrid) {
  this->uvGrid = uvGrid;
  inverseCartographicProjection = createInverseCartographicTransformFilter(uvGrid)->GetTransform();
}

void SpawnPointCallback::setBeached(const vtkSmartPointer<vtkIntArray> &ints) {
  this->particlesBeached = ints;
}
