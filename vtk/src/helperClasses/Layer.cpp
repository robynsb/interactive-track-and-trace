#include "Layer.h"
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

using std::string;

vtkSmartPointer<vtkRenderer> Layer::getLayer() {
  return this->ren;
}

void Layer::updateData(int t) {
}


void Layer::addObserver(const char *event, vtkCommand *observer) {
  this->getLayer()->GetRenderWindow()->GetInteractor()->AddObserver(event, observer);
}
