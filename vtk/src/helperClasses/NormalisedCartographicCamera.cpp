#include "NormalisedCartographicCamera.h"
#include <vtkMatrix4x4.h>

vtkSmartPointer<vtkCamera> createNormalisedCartographicCamera() {
    const double XMin = -15.875;
    const double XMax = 12.875;
    const double YMin = 46.125;
    const double YMax = 62.625;

    double farClipPlane = 100;
    double nearClipPlane = 1;
    double eyeTransform[] = {
            2/(XMax-XMin), 0, 0, -(XMax+XMin)/(XMax-XMin),
            0, 2/(YMax-YMin), 0, -(YMax+YMin)/(YMax-YMin),
            0, 0, 2/(nearClipPlane-farClipPlane), -(farClipPlane+nearClipPlane)/(farClipPlane-nearClipPlane),
            0, 0, 0, 1
    };

    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->ParallelProjectionOn();  // Enable parallel projection
    camera->UseExplicitProjectionTransformMatrixOn();

////    // Calculate the center and the size of the view
    double centerX = (XMax + XMin) / 2.0;
    double centerY = (YMax + YMin) / 2.0;
    double width = XMax - XMin;
    double height = YMax - YMin;
////    // Set the camera position, focal point, and view up
//    camera->SetPosition(centerX, centerY, 1000);  // Place the camera above the center
//    camera->SetFocalPoint(centerX, centerY, 0);  // Look at the center
//    camera->SetViewUp(0, 1, 0);                  // Set the up vector to be along the Y-axis
////
////    // Set parallel scale
//    double parallelScale = std::max(width, height) / 2.0;
//    camera->SetParallelScale(parallelScale);

    vtkNew<vtkMatrix4x4> projectionMatrix;
    projectionMatrix->DeepCopy(eyeTransform);
    camera->SetExplicitProjectionTransformMatrix(projectionMatrix);
//    camera->SetScreenBottomLeft(XMin, YMin, 0);
//    camera->SetScreenTopRight(XMax, YMax, 0);
    return camera;
}
