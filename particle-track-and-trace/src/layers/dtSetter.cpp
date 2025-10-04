#include "dtSetter.h"
#include "../commands/changeDtCommand.h"

void DTSetter::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  callback = vtkSmartPointer<ChangeDtCommand>::New(this->timer);
  interactor->AddObserver(vtkCommand::KeyPressEvent, callback);
}

DTSetter::DTSetter(const std::shared_ptr<Timer> &timer) : timer(timer) {}
