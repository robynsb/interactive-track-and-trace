#include "BackgroundImage.h"
#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageReader2.h>
#include <vtkTransformFilter.h>

using std::string;

BackgroundImage::BackgroundImage(string imagePath) : imagePath(imagePath) {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(0);
  this->ren->InteractiveOff();
  updateImage();
}


void BackgroundImage::updateImage() {
  vtkSmartPointer<vtkImageData> imageData;

  vtkSmartPointer<vtkImageReader2> imageReader;
  
  imageReader.TakeReference(this->readerFactory->CreateImageReader2(this->imagePath.c_str()));
  imageReader->SetFileName(this->imagePath.c_str());
  imageReader->Update();
  imageData = imageReader->GetOutput();

  // TODO: transform the iamge to the range [-1,1] and center it on (0,0)/
  // This will allow the backgorundImage to share a camera with our other layers.
  // Facilitating the cameraMovement callback.
  
  // vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter();
  // transformFilter->SetInputData(imageData);

  vtkNew<vtkImageActor> imageActor;
  imageActor->SetInputData(imageData);

  this->ren->AddActor(imageActor);


  // camera stuff
  // essentially sets the camera to the middle of the background, and points it at the background
  // TODO: extract this to its own function, separate from the background class.
  double origin[3], spacing[3];
  int extent[6];
  imageData->GetOrigin(origin);
  imageData->GetSpacing(spacing);
  imageData->GetExtent(extent);

  vtkCamera *camera = this->ren->GetActiveCamera();
  camera->ParallelProjectionOn();

  double xc = origin[0] + 0.5 * (extent[0] + extent[1]) * spacing[0];
  double yc = origin[1] + 0.5 * (extent[2] + extent[3]) * spacing[1];
  double yd = (extent[3] - extent[2] + 1) * spacing[1];
  double d = camera->GetDistance();
  camera->SetParallelScale(0.5 * yd);
  camera->SetFocalPoint(xc, yc, 0.0);
  camera->SetPosition(xc, yc, d);
}


string BackgroundImage::getImagePath() {
  return this->imagePath;
}

void BackgroundImage::setImagePath(string imagePath) {
  this->imagePath = imagePath;
  updateImage();
}


void BackgroundImage::setCamera(vtkCamera *cam) {
  // TODO: fix the camera for this layer so this intentionally empty override can be removed.
}
