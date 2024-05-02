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
  /** gets the vtkRenderer to assign it to the vtkRenderWindow of the program class.
   * @return pointer to the vtkRenderer of this class.
   */
  virtual vtkSmartPointer<vtkRenderer> getLayer();


  /** updates the data in the layer to reflect the given timestamp.
    * @param t : the timestamp which the data should reflect.
    */
  virtual void updateData(int t);
};

#endif
