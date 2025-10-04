#pragma once

#include <vtkCallbackCommand.h>
#include "../layers/Timer.h"

class ChangeDtCommand : public vtkCallbackCommand {
public:
  ChangeDtCommand();
  static ChangeDtCommand* New(Timer *timer);
  void Execute(vtkObject* caller, unsigned long eventId, void* vtkNotUsed(callData)) override;

  void setTimer(Timer t);
private:
  Timer *timer;
};
