#include "DisplaySplashScreenCommand.h"

#include <vtkRenderWindowInteractor.h>

void DisplaySplashScreenCommand::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  if(eid == vtkCommand::KeyPressEvent) {
    if(strcmp(intr->GetKeySym(), "space") == 0) {
      toggle();
    }
  }
}

DisplaySplashScreenCommand::DisplaySplashScreenCommand(std::function<void()> toggle) : toggle(toggle) {}

void DisplaySplashScreenCommand::setToggle(const std::function<void()> &toggle) {
  this->toggle = toggle;
}

DisplaySplashScreenCommand::DisplaySplashScreenCommand() {}

DisplaySplashScreenCommand *DisplaySplashScreenCommand::New() {
  return new DisplaySplashScreenCommand;
}
