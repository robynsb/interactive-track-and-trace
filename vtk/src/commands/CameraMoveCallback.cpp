#include "CameraMoveCallback.h"

#include <vtkVertex.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindow.h>

using std::string;

void CameraMoveCallback::Execute(vtkObject *caller, unsigned long evId,
                                 void *callData) {
  // Note the use of reinterpret_cast to cast the caller to the expected type.
  auto interactor = reinterpret_cast<vtkRenderWindowInteractor *>(caller);

  switch (evId) {
    case vtkCommand::KeyPressEvent:
      pan(interactor->GetKeySym());
      break;
    case vtkCommand::MouseWheelForwardEvent:
      zoom(true);
      break;
    case vtkCommand::MouseWheelBackwardEvent:
      zoom(false);
      break;
    default:
      break;
  }
}

void CameraMoveCallback::zoom(const bool in) {
  double pos[3];
  this->cam->GetPosition(pos);

  if (in) {
    pos[2] -= 50;
  } else {
    pos[2] += 50;
  }
  this->cam->SetPosition(pos);

}

void CameraMoveCallback::pan(const string dir) {
  double pos[3];
  this->cam->GetPosition(pos);

  if (dir == "Left" or dir == "h") {
    pos[0] -= 1;
    this->cam->SetPosition(pos);
  } else if (dir == "Up" or dir == "j" ) {
    pos[1] += 1;
    this->cam->SetPosition(pos);
  } else if (dir == "Right" or dir == "k" ) {
    pos[0] += 1;
    this->cam->SetPosition(pos);
  } else if (dir == "Down" or dir == "l" ) {
    pos[1] -= 1;
    this->cam->SetPosition(pos);
  }
}

CameraMoveCallback::CameraMoveCallback() : cam(nullptr) {}

CameraMoveCallback *CameraMoveCallback::New(vtkCamera *cam) {
  auto me = new CameraMoveCallback;
  me->setCam(cam);
  return me;
}

void CameraMoveCallback::setCam(const vtkSmartPointer<vtkCamera> &cam) {
    this->cam = cam;
}
