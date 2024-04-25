#include "EGlyphLayer.h"


EGlyphLayer::EGlyphLayer() {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(1);
  this->ren->InteractiveOff();
}
