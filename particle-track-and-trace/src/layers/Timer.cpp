#include "Timer.h"
#include "../commands/TimerCallbackCommand.h"
#include <vtkSmartPointer.h>

void Timer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  callback = vtkSmartPointer<TimerCallbackCommand>::New();
  callback->setProgram(program.get());
  callback->SetClientData(this);
  callback->setDt(dt);
  interactor->AddObserver(vtkCommand::TimerEvent, callback);
  interactor->AddObserver(vtkCommand::KeyPressEvent, callback);
  interactor->CreateRepeatingTimer(16); // 60 fps == 1000 / 60 == 16.7 ms per frame
}

Timer::Timer(const std::shared_ptr<Program> &program, int dt) : program(program), dt(dt) {}

void Timer::setPaused(bool val) {
  callback->setPaused(val);
}

void Timer::resetTime() {
  callback->resetTime();
}

void Timer::handleGameOver() {
  setPaused(true);
  resetTime();
}
