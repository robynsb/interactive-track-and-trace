#include "Layer.h"

using std::string;

vtkSmartPointer<vtkRenderer> Layer::getLayer() {
  return this->ren;
}
