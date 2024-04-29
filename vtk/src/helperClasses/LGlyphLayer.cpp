#include "LGlyphLayer.h"


LGlyphLayer::LGlyphLayer() {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(2);
}

void LGlyphLayer::updateData(short n) {

}
