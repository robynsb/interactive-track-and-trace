#include "DisplayEulerCommand.h"

#include <vtkRenderWindowInteractor.h>

void DisplayEulerCommand::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  if(eid == vtkCommand::KeyPressEvent) {
    if(strcmp(intr->GetKeySym(), "u") == 0) {
      toggle();
    }
  }
}

DisplayEulerCommand::DisplayEulerCommand(std::function<void()> toggle) : toggle(toggle) {}

void DisplayEulerCommand::setToggle(const std::function<void()> &toggle) {
  this->toggle = toggle;
}

DisplayEulerCommand::DisplayEulerCommand() {}

DisplayEulerCommand *DisplayEulerCommand::New() {
  return new DisplayEulerCommand;
}
