#include "Layer.h"
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

using std::string;

vtkSmartPointer<vtkRenderer> Layer::getLayer() {
  return this->ren;
}

void Layer::updateData(int t) {
}

void Layer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
    // By default, do nothing.
}
