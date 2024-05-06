#include "CartographicTransformation.h"
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

vtkSmartPointer<vtkCamera> createNormalisedCamera() {
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->ParallelProjectionOn();  // Enable parallel projection

    camera->SetPosition(0, 0, 1000);  // Place the camera above the center
    camera->SetFocalPoint(0, 0, 0);  // Look at the center
    camera->SetViewUp(0, 1, 0); // Set the up vector to be along the Y-axis
    camera->SetParallelScale(1); // x,y in [-1, 1]

    return camera;
}

vtkSmartPointer<vtkMatrix4x4> getCartographicTransformMatrix(const std::shared_ptr<UVGrid> uvGrid) {
    const double XMin = uvGrid->lons.front();
    const double XMax = uvGrid->lons.back();
    const double YMin = uvGrid->lats.front();
    const double YMax = uvGrid->lats.back();

    double eyeTransform[] = {
            2/(XMax-XMin), 0, 0, -(XMax+XMin)/(XMax-XMin),
            0, 2/(YMax-YMin), 0, -(YMax+YMin)/(YMax-YMin),
            0, 0, 1, 0,
            0, 0, 0, 1
    };

    auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    matrix->DeepCopy(eyeTransform);
    return matrix;
}

// Assumes Normalised camera is used
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid) {
    vtkNew<vtkTransform> transform;

    transform->SetMatrix(getCartographicTransformMatrix(uvGrid));

    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetTransform(transform);

    return transformFilter;
}
