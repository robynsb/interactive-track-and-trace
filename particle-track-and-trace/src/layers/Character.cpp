#include <cassert>

#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkTransformFilter.h>
#include <vtkAppendFilter.h>

#include "Character.h"
#include "../CartographicTransformation.h"

using namespace std;

Character::Character(std::shared_ptr<UVGrid> uvGrid) {
  controller = vtkSmartPointer<CharacterMoveCallback>::New();

  position = vtkSmartPointer<vtkPoints>::New();
  position->InsertPoint(0, 6.513089433595266, 53.44059997086552, 0); // Groningen

  data = vtkSmartPointer<vtkPolyData>::New();
  data->SetPoints(position);

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter(uvGrid);
  transformFilter->SetInputData(data);
  transformFilter->Update();
  cameraTransform.TakeReference(transformFilter->GetTransform());

  arrowSource = vtkSmartPointer<vtkGlyphSource2D>::New();
//  arrowSource->SetGlyphTypeToArrow();
  arrowSource->SetGlyphTypeToTriangle();
  arrowSource->SetScale(0.02);
  arrowSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph2D->SetInputConnection(transformFilter->GetOutputPort());
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper>mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  actor->GetProperty()->SetColor(0, 0, 0);
  actor->GetProperty()->SetOpacity(0.2);

  ren->AddActor(actor);
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
  clampCamera(cameraTransform->TransformPoint(position->GetPoint(0)));
//  position->SetPoint(0, sin(time), cos(time), 0);
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
  position->SetPoint(0, point[0] + cos(angleRadians)*velocity, point[1] + sin(angleRadians)*velocity, 0);
  position->Modified();
}

void Character::updateDirection() {
  arrowSource->SetRotationAngle(45 + angleRadians * (180.0 / M_PI));
  arrowSource->Update();
}

void Character::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  interactor->AddObserver(vtkCommand::KeyPressEvent, controller);
  interactor->AddObserver(vtkCommand::KeyReleaseEvent, controller);
}

void Character::clampCamera(double pos[3]) {
  auto cam = ren->GetActiveCamera();
  double ogpos[3];
  cam->GetPosition(ogpos);

  double scale = cam->GetParallelScale();

  // only check the x,y coords of the camera; we don't care about z
  for (int i=0; i < 2; i++) {
    //boundary cond: scale+|pos| < 1.
    if (abs(pos[i])+scale > 1.01) {
      if (pos[i] >= 0) {
        pos[i] = 1 - scale;
      } else {
        pos[i] = scale - 1;
      }
    }
  }

  cam->SetPosition(pos[0], pos[1], ogpos[2]);
  cam->SetFocalPoint(pos[0], pos[1], 0);
}

vtkSmartPointer<vtkPoints> Character::getPosition() {
  return position;
}
