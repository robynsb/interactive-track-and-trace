#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransformFilter.h>
#include <vtkPlaneSource.h>
#include <vtkGlyph2D.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkTransform.h>

#include "Health.h"
#include "../CartographicTransformation.h"

void Health::placeBackgroundHealth() {
  vtkNew<vtkPoints> position;
  position->InsertPoint(0, 0.9, -0.85, 0);

  vtkNew<vtkPolyData> data;
  data->SetPoints(position);

  // Create a plane
  vtkNew<vtkPlaneSource> plane;
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);

  vtkNew<vtkTransform> scaleIntoRectangle;
  scaleIntoRectangle->Scale(0.1, 0.2, 1);
  vtkNew<vtkTransformFilter> rectangle;
  rectangle->SetTransform(scaleIntoRectangle);
  rectangle->SetInputConnection(plane->GetOutputPort());

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(rectangle->GetOutputPort());
  glyph2D->SetInputData(data);
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  actor->GetProperty()->SetColor(0.227, 0.188, 0.259);
  actor->GetProperty()->SetOpacity(1);

  ren->AddActor(actor);
}

void Health::placeHealth() {
  vtkNew<vtkPoints> position;
  position->InsertPoint(0, 0.9, -0.85, 0);

  vtkNew<vtkPolyData> data;
  data->SetPoints(position);

  // Create a plane
  vtkNew<vtkPlaneSource> plane;
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);

//  scaleIntoRectangle->Scale(0.08, 0.1, 1);
//  scaleIntoRectangle->Translate(0, -0.35, 0);
  vtkNew<vtkTransform> scaleIntoRectangle;
  scaleIntoRectangle->Scale(0.08, h, 1);
  scaleIntoRectangle->Translate(0, 0, 0);
  vtkNew<vtkTransformFilter> rectangle;
  rectangle->SetTransform(scaleIntoRectangle);
  rectangle->SetInputConnection(plane->GetOutputPort());

  healthBarScaler = vtkSmartPointer<vtkTransform>::New();
  healthBarScaler->Identity();
  vtkNew<vtkTransformFilter> scaledRectangle;
  scaledRectangle->SetTransform(healthBarScaler);
  scaledRectangle->SetInputConnection(rectangle->GetOutputPort());

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(scaledRectangle->GetOutputPort());
  glyph2D->SetInputData(data);
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  actor->GetProperty()->SetColor(0.165, 0.988, 0.596);
  actor->GetProperty()->SetOpacity(1);

  ren->AddActor(actor);
}

Health::Health(const std::shared_ptr<GameoverCallback> &gameoverCallback): gameoverCallback(gameoverCallback) {
  placeBackgroundHealth();
  placeHealth();
}

void Health::setCamera(vtkCamera *camera) {
  getLayer()->SetActiveCamera(createNormalisedCamera());
}

void Health::updateData(int t) {
  if (health > 0.25) setHealth(health-healthLossRate);
  else setHealth(health-healthLossRate/2);
  if (gracePeriod > 0) gracePeriod--;
}

void Health::changeHealth(double healthChange) {
  if (healthChange < 0 and gracePeriod > 0) {
    return;
  }

  setHealth(health + healthChange);
}

void Health::setHealth(double health) {
  if (health < 0) {
    gameoverCallback->handleGameOver();
    return;
  }
  this->health = health;
  healthBarScaler->Identity();
  healthBarScaler->Translate(0, -h*(1-health)/2, 0);
  healthBarScaler->Scale(1, health, 1);
}

void Health::handleGameOver() {
  health = 1;
  setHealth(health);
}

void Health::grace() {
  gracePeriod = GRACEPERIOD;
}
