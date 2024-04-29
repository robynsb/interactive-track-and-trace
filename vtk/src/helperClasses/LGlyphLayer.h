#ifndef LGLYPHLAYER_H
#define LGLYPHLAYER_H

#include "Layer.h"
#include <vtkPolyData.h>

class LGlyphLayer : public Layer {
private:
  vtkSmartPointer<vtkPoints> points;
  vtkSmartPointer<vtkPolyData> data;

public:
  LGlyphLayer();
  void updateData(short t);

};

#endif
