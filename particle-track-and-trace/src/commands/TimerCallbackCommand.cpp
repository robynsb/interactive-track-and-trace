#include "TimerCallbackCommand.h"
#include "../Program.h"


// TODO: add getter/setters to attributes for customizability.
TimerCallbackCommand::TimerCallbackCommand() : dt(3600), maxTime(3600*24*365), time(0) {}

TimerCallbackCommand* TimerCallbackCommand::New(Program *program) {
  TimerCallbackCommand *cb = new TimerCallbackCommand();
  cb->setProgram(program);
  cb->setPaused(true);
  return cb;
}

void TimerCallbackCommand::Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  
  if (eventId == vtkCommand::KeyPressEvent and not strcmp("space", intr->GetKeySym())) {
    this->paused = ! this->paused;
  } else if (eventId == vtkCommand::TimerEvent and not this->paused) {
    this->time += this->dt;
    if (this->time >= this->maxTime) {
      time = dt;
    }

    this->program->updateData(this->time);
  }
}

void TimerCallbackCommand::setProgram(Program *program) {
  this->program = program;
}


void TimerCallbackCommand::setPaused(const bool val) {
  this->paused = val;
}

void TimerCallbackCommand::setDt(int dt) {
  this->dt = dt;
}
