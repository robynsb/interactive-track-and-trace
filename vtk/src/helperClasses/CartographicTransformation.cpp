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

vtkSmartPointer<vtkMatrix4x4> getCartographicTransformMatrix() {
    const double XMin = -15.875;
    const double XMax = 12.875;
    const double YMin = 46.125;
    const double YMax = 62.625;

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
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter() {
    vtkNew<vtkTransform> transform;

    transform->SetMatrix(getCartographicTransformMatrix());

    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetTransform(transform);

    return transformFilter;
}
