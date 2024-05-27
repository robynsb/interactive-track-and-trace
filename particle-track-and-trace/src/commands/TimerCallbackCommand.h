#ifndef TIMERCALLBACKCOMMAND_H
#define TIMERCALLBACKCOMMAND_H

#include <vtkCallbackCommand.h>
#include "../Program.h"

class TimerCallbackCommand : public vtkCallbackCommand {
public:
  TimerCallbackCommand();
  static TimerCallbackCommand* New(Program *program);
  void Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) override;

  void setProgram(Program *program);
  void setPaused(bool val);
  void resetTime();
  void setDt(int dt);

private:
  int time;
  int dt;
  int maxTime;
  bool paused;
  Program *program;
};

#endif
