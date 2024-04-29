#ifndef EGLYPHLAYER_H
#define EGLYPHLAYER_H

#include "Layer.h"
#include <vtkPolyData.h>

class EGlyphLayer : public Layer {
private:
  vtkSmartPointer<vtkPolyData> data;

  void readCoordinates();

public:
  EGlyphLayer();
  void updateData(short t);

};


#endif
