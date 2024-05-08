#include "CartographicTransformation.h"
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkGeoProjection.h>
#include <vtkGeoTransform.h>
#include <vtkGeneralTransform.h>

vtkSmartPointer<vtkCamera> createNormalisedCamera() {
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->ParallelProjectionOn();  // Enable parallel projection

    camera->SetPosition(0, 0, 1000);  // Place the camera above the center
    camera->SetFocalPoint(0, 0, 0);  // Look at the center
    camera->SetViewUp(0, 1, 0); // Set the up vector to be along the Y-axis
    camera->SetParallelScale(1); // x,y in [-1, 1]

    return camera;
}

//vtkSmartPointer<vtkMatrix4x4> getCartographicTransformMatrix(const std::shared_ptr<UVGrid> uvGrid) {
//    const double XMin = uvGrid->lons.front();
//    const double XMax = uvGrid->lons.back();
//    const double YMin = uvGrid->lats.front();
//    const double YMax = uvGrid->lats.back();
//
//    double eyeTransform[] = {
//            2/(XMax-XMin), 0, 0, -(XMax+XMin)/(XMax-XMin),
//            0, 2/(YMax-YMin), 0, -(YMax+YMin)/(YMax-YMin),
//            0, 0, 1, 0,
//            0, 0, 0, 1
//    };
//
//    auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
//    matrix->DeepCopy(eyeTransform);
//    return matrix;
//}

// Assumes Normalised camera is used
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid) {
  auto proj = vtkSmartPointer<vtkGeoProjection>::New();
  proj->SetName("merc");

  auto geoTransform = vtkSmartPointer<vtkGeoTransform>::New();
  geoTransform->SetDestinationProjection(proj);

  const double XMin = -15.875;
  const double XMax = 12.875;
  const double YMin = 46.125;
  const double YMax = 62.625;

  double bottomLeft[3] = {XMin, YMin, 0};
  double topRight[3] = {XMax, YMax, 0};
  geoTransform->TransformPoint(bottomLeft, bottomLeft);
  geoTransform->TransformPoint(topRight, topRight);

  double width = topRight[0] - bottomLeft[0];
  double height = topRight[1] - bottomLeft[1];

  auto scaleIntoNormalisedSpace = vtkSmartPointer<vtkTransform>::New();
  scaleIntoNormalisedSpace->Scale(2/(width), 2/(height), 1);
  scaleIntoNormalisedSpace->Translate(-(bottomLeft[0]+topRight[0])/2, -(bottomLeft[1] + topRight[1])/2, 0);

  auto totalProjection = vtkSmartPointer<vtkGeneralTransform>::New();
  totalProjection->Identity();
  totalProjection->Concatenate(scaleIntoNormalisedSpace);
  totalProjection->Concatenate(geoTransform);

  vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetTransform(totalProjection);

  return transformFilter;
}

vtkSmartPointer<vtkTransformFilter> createInverseCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid) {
  auto proj = vtkSmartPointer<vtkGeoProjection>::New();
  proj->SetName("merc");

  auto geoTransform = vtkSmartPointer<vtkGeoTransform>::New();
  geoTransform->SetDestinationProjection(proj);

  const double XMin = -15.875;
  const double XMax = 12.875;
  const double YMin = 46.125;
  const double YMax = 62.625;

  double bottomLeft[3] = {XMin, YMin, 0};
  double topRight[3] = {XMax, YMax, 0};
  geoTransform->TransformPoint(bottomLeft, bottomLeft);
  geoTransform->TransformPoint(topRight, topRight);
  geoTransform->Inverse();

  double width = topRight[0] - bottomLeft[0];
  double height = topRight[1] - bottomLeft[1];

  auto scaleIntoNormalisedSpace = vtkSmartPointer<vtkTransform>::New();
  scaleIntoNormalisedSpace->Scale(2/(width), 2/(height), 1);
  scaleIntoNormalisedSpace->Translate(-(bottomLeft[0]+topRight[0])/2, -(bottomLeft[1] + topRight[1])/2, 0);
  scaleIntoNormalisedSpace->Inverse();

  auto totalProjection = vtkSmartPointer<vtkGeneralTransform>::New();
  totalProjection->Identity();
  totalProjection->Concatenate(geoTransform);
  totalProjection->Concatenate(scaleIntoNormalisedSpace);

  vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetTransform(totalProjection);

  return transformFilter;
}
