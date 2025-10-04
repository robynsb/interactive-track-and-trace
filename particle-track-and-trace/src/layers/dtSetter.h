#pragma once

#include "Layer.h"
#include "../Program.h"
#include "../commands/changeDtCommand.h"
#include "Timer.h"

class DTSetter : public Layer {
private:
  std::shared_ptr<Timer> timer;
  vtkSmartPointer<ChangeDtCommand> callback;
public:
  DTSetter(const std::shared_ptr<Timer> &timer);
  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;
};
