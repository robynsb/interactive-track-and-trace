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

#include "Character.h"
#include "../CartographicTransformation.h"

using namespace std;

Character::Character(std::shared_ptr<UVGrid> uvGrid, string path, std::shared_ptr<Camera> camera):
  uvGrid(uvGrid), camera(camera) {
  controller = vtkSmartPointer<CharacterMoveCallback>::New();

  position = vtkSmartPointer<vtkPoints>::New();
  position->InsertPoint(0, 6.513089433595266, 53.44059997086552, 0); // Groningen

  data = vtkSmartPointer<vtkPolyData>::New();
  data->SetPoints(position);

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter(uvGrid);
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
  vtkNew<vtkTexture> texture;
  texture->SetInputConnection(pngReader->GetOutputPort());

  vtkNew<vtkTextureMapToPlane> texturePlane;
  texturePlane->SetInputConnection(plane->GetOutputPort());

  vtkNew<vtkTransform> scaler;
  scaler->Scale(0.05, 0.05, 1.0);

  vtkNew<vtkTransformFilter> scaleFilter;
  scaleFilter->SetTransform(scaler);
  scaleFilter->SetInputConnection(texturePlane->GetOutputPort());

  rotater = vtkSmartPointer<vtkTransform>::New();
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

  vtkNew<vtkActor> texturedPlane;
  texturedPlane->SetMapper(mapper);
  texturedPlane->SetTexture(texture);

//  actor->GetProperty()->SetColor(0, 0, 0);
//  actor->GetProperty()->SetOpacity(0.2);

  ren->AddActor(texturedPlane);
}


void Character::updateData(int t) {
  double time = (double) t/10000;
  if (controller->getIsGoingLeft()) {
    angleRadians += ROTATIONSTEP;
  }
  if (controller->getIsGoingRight()) {
    angleRadians -= ROTATIONSTEP;
  }
  updateDirection();
  if(controller->getIsAccelerating() and !controller->getIsReversing()) {
    throttle += ACCELERATESTEP;
  }
  if (!controller->getIsAccelerating()) {
    if(throttle > 1) {
      throttle = 1;
    } else if (DECELLERATION < throttle ) {
      throttle -= DECELLERATION;
    } else {
      throttle = 0;
    }
  }
  updateVelocity();
  updatePosition();
  camera->clampCamera(cameraTransform->TransformPoint(position->GetPoint(0)));
}

double easingFunction(double t) {
  assert(t >= 0);
  if (t < 0.5) {
    return 2*t*t;
  } else {
    return 1-1/(5*(2*t-0.5)-1);
  }
}

void Character::updateVelocity() {
  velocity = MAXVELOCITY * easingFunction(throttle);
}

void Character::updatePosition() {
  double point[3];
  position->GetPoint(0, point);
  point[0] += cos(angleRadians)*velocity*SCALEHORIZONTALVELOCITY;
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

void Character::updateDirection() {
  rotater->Identity();
  rotater->RotateZ(- 25+ angleRadians * (180.0 / M_PI));
  rotater->Update();
}

void Character::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  interactor->AddObserver(vtkCommand::KeyPressEvent, controller);
  interactor->AddObserver(vtkCommand::KeyReleaseEvent, controller);
}

vtkSmartPointer<vtkPoints> Character::getPosition() {
  return position;
}
