#include "CartographicTransformation.h"
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkGeoProjection.h>
#include <vtkGeoTransform.h>
#include <vtkGeneralTransform.h>

vtkSmartPointer<vtkCamera> createNormalisedCamera() {
  vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
  camera->ParallelProjectionOn(); // Enable parallel projection

  camera->SetPosition(0, 0, 1000);  // Place the camera above the center
  camera->SetFocalPoint(0, 0, 0);  // Look at the center
  camera->SetViewUp(0, 1, 0); // Set the up vector to be along the Y-axis
  camera->SetParallelScale(1); // x,y in [-1, 1]

  return camera;
}

// Assumes Normalised camera is used
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter(const UVGrid &uvGrid) {
  auto proj = vtkSmartPointer<vtkGeoProjection>::New();
  proj->SetName("merc");

  auto geoTransform = vtkSmartPointer<vtkGeoTransform>::New();
  geoTransform->SetDestinationProjection(proj);

  const double XMin = uvGrid.lonMin();
  const double XMax = uvGrid.lonMax();
  const double YMin = uvGrid.latMin();
  const double YMax = uvGrid.latMax();

  double bottomLeft[3] = {XMin, YMin, 0};
  double topRight[3] = {XMax, YMax, 0};
  geoTransform->TransformPoint(bottomLeft, bottomLeft);
  geoTransform->TransformPoint(topRight, topRight);

  double width = topRight[0] - bottomLeft[0];
  double height = topRight[1] - bottomLeft[1];

  auto scaleIntoNormalisedSpace = vtkSmartPointer<vtkTransform>::New();
  scaleIntoNormalisedSpace->Scale(2 / (width), 2 / (height), 1);
  scaleIntoNormalisedSpace->Translate(-(bottomLeft[0] + topRight[0]) / 2, -(bottomLeft[1] + topRight[1]) / 2, 0);

  auto totalProjection = vtkSmartPointer<vtkGeneralTransform>::New();
  totalProjection->Identity();
  totalProjection->Concatenate(scaleIntoNormalisedSpace);
  totalProjection->Concatenate(geoTransform);

  vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetTransform(totalProjection);

  return transformFilter;
}

vtkSmartPointer<vtkTransformFilter> createInverseCartographicTransformFilter(const UVGrid &uvGrid) {
  auto proj = vtkSmartPointer<vtkGeoProjection>::New();
  proj->SetName("merc");

  auto geoTransform = vtkSmartPointer<vtkGeoTransform>::New();
  geoTransform->SetDestinationProjection(proj);

  const double XMin = uvGrid.lonMin();
  const double XMax = uvGrid.lonMax();
  const double YMin = uvGrid.latMin();
  const double YMax = uvGrid.latMax();

  double bottomLeft[3] = {XMin, YMin, 0};
  double topRight[3] = {XMax, YMax, 0};
  geoTransform->TransformPoint(bottomLeft, bottomLeft);
  geoTransform->TransformPoint(topRight, topRight);
  geoTransform->Inverse();

  double width = topRight[0] - bottomLeft[0];
  double height = topRight[1] - bottomLeft[1];

  auto scaleIntoNormalisedSpace = vtkSmartPointer<vtkTransform>::New();
  scaleIntoNormalisedSpace->Scale(2 / (width), 2 / (height), 1);
  scaleIntoNormalisedSpace->Translate(-(bottomLeft[0] + topRight[0]) / 2, -(bottomLeft[1] + topRight[1]) / 2, 0);
  scaleIntoNormalisedSpace->Inverse();

  auto totalProjection = vtkSmartPointer<vtkGeneralTransform>::New();
  totalProjection->Identity();
  totalProjection->Concatenate(geoTransform);
  totalProjection->Concatenate(scaleIntoNormalisedSpace);

  vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetTransform(totalProjection);

  return transformFilter;
}