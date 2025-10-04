#include "changeDtCommand.h"
#include "../layers/Timer.h"


// TODO: add getter/setters to attributes for customizability.
// TODO: maxTime: hard coded values?!
ChangeDtCommand::ChangeDtCommand() : dt(3600), maxTime(3600*24*365), time(0) {}

ChangeDtCommand* ChangeDtCommand::New(Timer *timer) {
  ChangeDtCommand *cb = new ChangeDtCommand();
  cb->setTimer(timer);
  return cb;
}

void ChangeDtCommand::Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  
  if (eventId == vtkCommand::KeyPressEvent and not strcmp("o", intr->GetKeySym())) {
    timer->changeDT(-1000);
  } else if if (eventId == vtkCommand::KeyPressEvent and not strcmp("p", intr->GetKeySym())) {
    timer->changeDT(1000);
  }
}

void ChangeDtCommand::setTimer(Timer *timer) {
  this->timer = timer;
}

