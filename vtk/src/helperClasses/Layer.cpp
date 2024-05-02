#include "Layer.h"

using std::string;

vtkSmartPointer<vtkRenderer> Layer::getLayer() {
  return this->ren;
}

void Layer::updateData(int t) {
  cout << "wrong function dimwit" << endl;
}
