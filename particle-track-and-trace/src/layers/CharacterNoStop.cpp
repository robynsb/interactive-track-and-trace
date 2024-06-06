#include <cassert>

#include <vtkGlyph2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransformFilter.h>
#include <vtkPNGReader.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>

#include "CharacterNoStop.h"
#include "../CartographicTransformation.h"

using namespace std;

CharacterNoStop::CharacterNoStop(std::shared_ptr<UVGrid> uvGrid, string path, std::shared_ptr<Camera> camera):
  uvGrid{uvGrid}, camera{camera} {

  position->InsertPoint(0, startLon, startLat, 0);

  data->SetPoints(position);

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter(*uvGrid);
  transformFilter->SetInputData(data);
  transformFilter->Update();
  cameraTransform.TakeReference(transformFilter->GetTransform());

  vtkNew<vtkPNGReader> pngReader;
  pngReader->SetFileName((path + "/bird.png").c_str());

  // Create a plane
  vtkNew<vtkPlaneSource> plane;
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);

  // Apply the texture
  texture->SetInputConnection(pngReader->GetOutputPort());

  vtkNew<vtkTextureMapToPlane> texturePlane;
  texturePlane->SetInputConnection(plane->GetOutputPort());

  vtkNew<vtkTransform> scaler;
  scaler->Scale(0.05, 0.05, 1.0);

  vtkNew<vtkTransformFilter> scaleFilter;
  scaleFilter->SetTransform(scaler);
  scaleFilter->SetInputConnection(texturePlane->GetOutputPort());

  rotater->Identity();
  vtkNew<vtkTransformFilter> rotateFilter;
  rotateFilter->SetTransform(rotater);
  rotateFilter->SetInputConnection(scaleFilter->GetOutputPort());

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(rotateFilter->GetOutputPort());
  glyph2D->SetInputConnection(transformFilter->GetOutputPort());
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper>mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  texturedPlane->SetMapper(mapper);
  texturedPlane->SetTexture(texture);

  renderer->AddActor(texturedPlane);
}

void CharacterNoStop::updateData(int t) {
  double time = (double) t/10000;
  updateDirection();

  if( !clickingNecessaryForSteering or controller->isSteering()) {
    updateAngle();
  }
  updateDashProgress();
  updateVelocity();
  updatePosition();
  camera->clampCamera(cameraTransform->TransformPoint(position->GetPoint(0)));
}

void CharacterNoStop::updateAngle() {
  double desiredAngle = getDesiredAngle();
  double currentAngle = fmod(angleRadians, 2*M_PI);
  if (currentAngle > M_PI) {
    currentAngle -= 2*M_PI;
  }
  if (currentAngle < -M_PI) {
    currentAngle += 2*M_PI;
  }
  double signedDifference = desiredAngle - currentAngle;
  if (abs(signedDifference) < rotationStep ) {
    angleRadians = desiredAngle;
  } else {
    if(signedDifference > M_PI) {
      signedDifference = signedDifference - 2*M_PI;
    }
    if(signedDifference < -M_PI) {
      signedDifference = signedDifference + 2*M_PI;
    }
    angleRadians += signedDifference > 0 ? rotationStep : -rotationStep;
  }
}

double CharacterNoStop::getDesiredAngle() {
  auto [x, y] = controller->getDesiredDisplayPos();
  renderer->SetDisplayPoint(x, y, 0);
  renderer->DisplayToWorld();
  double desired[4];
  renderer->GetWorldPoint(desired);

  double point[3];
  position->GetPoint(0, point);
  cameraTransform->TransformPoint(point, point);
  double desiredDirection[2];
  desiredDirection[0] = desired[0] - point[0];
  desiredDirection[1] = desired[1] - point[1];
  return atan2(desiredDirection[1], desiredDirection[0]);
}

void CharacterNoStop::updateVelocity() {
  velocity = maxVelocity + getDashVelocityBonus();
}

void CharacterNoStop::updatePosition() {
  double point[3];
  position->GetPoint(0, point);
  point[0] += cos(angleRadians)*velocity*scaleHorizontalVelocity;
  point[1] += sin(angleRadians)*velocity;

  if (point[0] < uvGrid->lonMin()) {
    point[0] = uvGrid->lonMin();
  }
  if (point[0] > uvGrid->lonMax()) {
    point[0] = uvGrid->lonMax();
  }
  if (point[1] < uvGrid->latMin()) {
    point[1] = uvGrid->latMin();
  }
  if (point[1] > uvGrid->latMax()) {
    point[1] = uvGrid->latMax();
  }

  position->SetPoint(0, point);
  position->Modified();
}

void CharacterNoStop::updateDirection() {
  rotater->Identity();
  rotater->RotateZ(- 25+ angleRadians * (180.0 / M_PI));
  rotater->Update();
}

void CharacterNoStop::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, controller);
  interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, controller);
  interactor->AddObserver(vtkCommand::MouseMoveEvent, controller);
}

vtkSmartPointer<vtkPoints> CharacterNoStop::getPosition() {
  return position;
}

void CharacterNoStop::handleGameOver() {
  position->SetPoint(0, startLon, startLat, 0);
  dashProgress = 0;
  updateDashProgress();
}

void CharacterNoStop::dash() {
  dashProgress = dashDuration;
  dashing = true;
}

double CharacterNoStop::getDashVelocityBonus() {
  return dashProgress * dashVelocityBonus / dashDuration;
}

void CharacterNoStop::updateDashProgress() {
  if (dashing and dashProgress > 0) {
    dashProgress--;
    texturedPlane->GetProperty()->SetColor(12/255.0, 177/255.0, 98/255.0);
  }
  if (dashing and dashProgress == 0) {
    texturedPlane->GetProperty()->SetColor(1, 1, 1);
    dashing = false;
  }
}
