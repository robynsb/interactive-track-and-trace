#ifndef TIMER_H
#define TIMER_H

#include "Layer.h"
#include "../Program.h"
#include "../commands/TimerCallbackCommand.h"
#include "../gameovers/GameoverCallback.h"

class Timer : public Layer {
private:
  std::shared_ptr<Program> program;
  vtkSmartPointer<TimerCallbackCommand> callback;
  int dt;
public:
  void setPaused(bool val);

  void handleGameOver() override;

  void resetTime();
  Timer(const std::shared_ptr<Program> &program, int dt);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;
};


#endif //TIMER_H
