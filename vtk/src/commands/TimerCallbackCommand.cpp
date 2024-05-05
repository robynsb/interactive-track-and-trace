#include "TimerCallbackCommand.h"
#include "../helperClasses/Program.h"


TimerCallbackCommand::TimerCallbackCommand() : dt(3600), maxTime(3600*24*365), time(0) {}

TimerCallbackCommand* TimerCallbackCommand::New(Program *program) {
  TimerCallbackCommand *cb = new TimerCallbackCommand();
  cb->setProgram(program);
  return cb;
}

void TimerCallbackCommand::Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) {
  this->time += this->dt;

  if (this->time >= this->maxTime) {
    return;
    // TODO: how do we deal with reaching the end of the simulated dataset? Do we just stop simulating, loop back around? What about the location of the particles in this case? Just some ideas to consider, but we should iron this out pretty soon.
  }

  this->program->updateData(this->time);
}



void TimerCallbackCommand::setProgram(Program *program) {
  this->program = program;
}
