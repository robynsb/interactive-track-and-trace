//
// Created by Robin Sachsenweger Ballantyne on 27/05/2024.
//

#include "Timer.h"
#include "../commands/TimerCallbackCommand.h"

void Timer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  auto callback = vtkSmartPointer<TimerCallbackCommand>::New(program.get());
  callback->SetClientData(this);
  callback->setDt(dt);
  interactor->AddObserver(vtkCommand::TimerEvent, callback);
  interactor->AddObserver(vtkCommand::KeyPressEvent, callback);
  interactor->CreateRepeatingTimer(17); // 60 fps == 1000 / 60 == 16.7 ms per frame
}

Timer::Timer(const std::shared_ptr<Program> &program, int dt) : program(program), dt(dt) {}
