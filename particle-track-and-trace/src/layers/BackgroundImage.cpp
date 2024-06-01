#include "BackgroundImage.h"
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageChangeInformation.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageReader2.h>
#include <vtkMatrix4x4.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

using std::string;

BackgroundImage::BackgroundImage(string imagePath) : imagePath(imagePath) {
  this->ren->InteractiveOff();
  updateImage();
}


vtkSmartPointer<vtkMatrix4x4> BackgroundImage::getMatrix(const double x0, const double y0, const int xMax, const int yMax) {
    double eyeTransform[] = {
            2/(xMax-x0), 0, 0, -(xMax+x0)/(xMax-x0),
            0, 2/(yMax-y0), 0, -(yMax+y0)/(yMax-y0),
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    matrix->DeepCopy(eyeTransform);
    return matrix;
}


void BackgroundImage::updateImage() {

  // read image data
  vtkSmartPointer<vtkImageReader2> imageReader;
  imageReader.TakeReference(this->readerFactory->CreateImageReader2(this->imagePath.c_str()));
  imageReader->SetFileName(this->imagePath.c_str());
  imageReader->Update();

  // translate image such that the middle is at (0,0)
  vtkNew<vtkImageChangeInformation> imageCenterer;
  imageCenterer->SetInputConnection(imageReader->GetOutputPort());
  imageCenterer->CenterImageOn();
  imageCenterer->Update();

  // get some info from the data we'll need in a second
  vtkSmartPointer<vtkImageData> imageData = imageCenterer->GetOutput();
  double origin[3];
  int extent[6];
  imageData->GetOrigin(origin);
  imageData->GetExtent(extent);

  // map the imageData to a vtkPolydata so we can use a vtkTransform
  vtkNew<vtkImageDataGeometryFilter> imageDataGeometryFilter;
  imageDataGeometryFilter->SetInputData(imageData);
  imageDataGeometryFilter->Update();

//   setup the vtkTransform - this is where use the data from imageData we got earlier
  vtkNew<vtkTransform> transform;
  transform->SetMatrix(getMatrix(origin[0], origin[1], extent[1]+origin[0], extent[3]+origin[1]));
  vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetTransform(transform);
  transformFilter->SetInputConnection(imageDataGeometryFilter->GetOutputPort());
  transformFilter->Update();

  // Create a mapper and actor
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(transformFilter->GetOutputPort());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
    
  this->ren->AddActor(actor);
}


string BackgroundImage::getImagePath() {
  return this->imagePath;
}

void BackgroundImage::setImagePath(string imagePath) {
  this->imagePath = imagePath;
  updateImage();
}

