#include "BackgroundImage.h"
#include <vtkImageChangeInformation.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageReader2.h>
#include <vtkImageShiftScale.h>
#include <vtkMatrix4x4.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>

using std::string;

BackgroundImage::BackgroundImage(string imagePath) : imagePath(imagePath) {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(0);
  this->ren->InteractiveOff();
  updateImage();
}

vtkSmartPointer<vtkMatrix4x4> getMatrix() {
    const double XMin = 0;
    const double XMax = 661;
    const double YMin = 0;
    const double YMax = 661;

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


void BackgroundImage::updateImage() {

  vtkSmartPointer<vtkImageReader2> imageReader;
  
  imageReader.TakeReference(this->readerFactory->CreateImageReader2(this->imagePath.c_str()));
  imageReader->SetFileName(this->imagePath.c_str());
  imageReader->Update();

  vtkNew<vtkImageChangeInformation> imageCenterer;
  imageCenterer->SetInputConnection(imageReader->GetOutputPort());
  imageCenterer->CenterImageOn();
  imageCenterer->Update();

  vtkSmartPointer<vtkImageData> imageData = imageCenterer->GetOutput();

  // TODO: transform the iamge to the range [-1,1]
  // This will allow the backgorundImage to share a camera with our other layers.
  // Facilitating the cameraMovement callback.
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

  printf("%lf, %lf, %lf\n", origin[0], origin[1], origin[2]);
  printf("%lf, %lf, %lf\n", spacing[0], spacing[1], spacing[2]);
  printf("%d, %d, %d, ", extent[0], extent[1], extent[2]);
  printf("%d, %d, %d\n", extent[3], extent[4], extent[5]);

  vtkCamera *camera = this->ren->GetActiveCamera();
  camera->ParallelProjectionOn();

  double xc = origin[0] + 0.5 * (extent[0] + extent[1]) * spacing[0];
  double yc = origin[1] + 0.5 * (extent[2] + extent[3]) * spacing[1];
  double yd = (extent[3] - extent[2] + 1) * spacing[1];

  printf("%lf, %lf, %lf\n", xc, yc, yd);

  camera->SetParallelScale(0.5 * yd); // sets to 330; should be 1 ->  transform
  camera->SetFocalPoint(xc, yc, 0.0); // sets to 0,0,0; isnice
  camera->SetPosition(xc, yc, 1000); // sets to 0,0,1000; isnice
}


string BackgroundImage::getImagePath() {
  return this->imagePath;
}

void BackgroundImage::setImagePath(string imagePath) {
  this->imagePath = imagePath;
  updateImage();
}


void BackgroundImage::setCamera(vtkCamera *cam) {
  this->getLayer()->SetActiveCamera(cam);
  // TODO: fix the camera for this layer so this intentionally empty override can be removed.
}
