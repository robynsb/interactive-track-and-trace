#ifndef LAYER_H
#define LAYER_H

#include <vtkRenderer.h>

/** This class represents one abstract layer to be rendered to VTK.
  * It exists to manage multiple different layers under the Program class.
  */
class Layer {
protected:
  vtkSmartPointer<vtkRenderer> ren;

public:
  virtual vtkSmartPointer<vtkRenderer> getLayer();
};

#endif
