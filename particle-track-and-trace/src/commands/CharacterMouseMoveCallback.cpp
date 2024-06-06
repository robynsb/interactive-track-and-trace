#include "CharacterMouseMoveCallback.h"

#include <vtkRenderWindowInteractor.h>

void CharacterMouseMoveCallback::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  // Note the use of reinterpret_cast to cast the caller to the expected type.
  auto interactor = reinterpret_cast<vtkRenderWindowInteractor *>(caller);

  if (eid == vtkCommand::LeftButtonPressEvent) {
    isClicking = true;
  }
  if (eid == vtkCommand::LeftButtonReleaseEvent) {
    isClicking = false;
  }

  int x, y;
  interactor->GetEventPosition(x, y);

  desiredDisplayPos = {x, y};
}

CharacterMouseMoveCallback *CharacterMouseMoveCallback::New() {
  return new CharacterMouseMoveCallback;
}

CharacterMouseMoveCallback::CharacterMouseMoveCallback() {}

std::pair<double, double> CharacterMouseMoveCallback::getDesiredDisplayPos() const {
  return desiredDisplayPos;
}

bool CharacterMouseMoveCallback::isSteering() const {
  return isClicking;
}