#include "SpawnPointCallback.h"

#include <vtkVertex.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>

#include "CartographicTransformation.h"

void convertDisplayToWorld(vtkRenderer* renderer, int x, int y, double *worldPos) {
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
    inverseCartographicProjection->MultiplyPoint(worldPos, worldPos);
    cout << "clicked on lon = " << worldPos[0] << " and lat = " << worldPos[1] << endl;

    vtkIdType id = points->InsertNextPoint(worldPos[0], worldPos[1], 0);
    data->SetPoints(points);

    vtkSmartPointer<vtkVertex> vertex = vtkSmartPointer<vtkVertex>::New();
    vertex->GetPointIds()->SetId(0, id);

    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    vertices->InsertNextCell(vertex);
    data->SetVerts(vertices);
//    data->Modified(); // These might be needed im not sure.
//    ren->GetRenderWindow()->Render();
}


SpawnPointCallback::SpawnPointCallback() : data(nullptr), points(nullptr), inverseCartographicProjection(nullptr) {
    inverseCartographicProjection = getCartographicTransformMatrix();
    inverseCartographicProjection->Invert();
}

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
