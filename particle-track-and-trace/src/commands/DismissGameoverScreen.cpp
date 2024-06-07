#include <vtkRenderWindowInteractor.h>
#include "DismissGameoverScreen.h"

void DismissGameoverScreen::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  if(eid == vtkCommand::KeyPressEvent) {
    if(strcmp(intr->GetKeySym(), "space") == 0) {
      dismiss();
    }
  }
}

DismissGameoverScreen::DismissGameoverScreen(std::function<void()> dismiss) : dismiss(dismiss) {}

void DismissGameoverScreen::setDismiss(const std::function<void()> &dismiss) {
  this->dismiss = dismiss;
}

DismissGameoverScreen::DismissGameoverScreen() {}

DismissGameoverScreen *DismissGameoverScreen::New() {
  return new DismissGameoverScreen;
}
