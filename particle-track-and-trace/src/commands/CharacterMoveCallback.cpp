#include <vtkRenderWindowInteractor.h>
#include "CharacterMoveCallback.h"

CharacterMoveCallback::CharacterMoveCallback() : isGoingRight(false),
                                                 isReversing(false),
                                                 isAccelerating(false),
                                                 isGoingLeft(false) {}

CharacterMoveCallback *CharacterMoveCallback::New() {
  return new CharacterMoveCallback;
}

void CharacterMoveCallback::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  switch (eid) {
    case vtkCommand::KeyPressEvent:
      keyPressed(intr->GetKeySym());
      break;
    case vtkCommand::KeyReleaseEvent:
      keyReleased(intr->GetKeySym());
      break;
  }
}

void CharacterMoveCallback::keyPressed(const std::string dir) {
  if (dir == "Left") {
    isGoingLeft = true;
  } else if (dir == "Right") {
    isGoingRight = true;
  } else if (dir == "Up") {
    isAccelerating = true;
  } else if (dir == "Down") {
    isReversing = true;
  }
}

void CharacterMoveCallback::keyReleased(const std::string dir) {
  if (dir == "Left") {
    isGoingLeft = false;
  } else if (dir == "Right") {
    isGoingRight = false;
  } else if (dir == "Up") {
    isAccelerating = false;
  } else if (dir == "Down") {
    isReversing = false;
  }
}

bool CharacterMoveCallback::getIsAccelerating() const {
  return isAccelerating;
}

bool CharacterMoveCallback::getIsReversing() const {
  return isReversing;
}

bool CharacterMoveCallback::getIsGoingLeft() const {
  return isGoingLeft;
}

bool CharacterMoveCallback::getIsGoingRight() const {
  return isGoingRight;
}
