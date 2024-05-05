#ifndef PROGRAM_H
#define PROGRAM_H

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "layers/Layer.h"

/** This class manages the upper levels of the vtk pipeline; it has attributes for the vtkrenderWindow and a vector of Layers to represent a variable number of vtkRenderers.
  * It can also set up a vtkTimer by connecting an instance of TimerCallbackCommand with its contained vtkRenderWindowInteractor.
  */ 
class Program {
private:
  /** This attribute models a variable number of vtkRenderers, managed through the abstract Layer class.
    */ 
  std::vector<Layer *> layers;

  /** The window this program's layers render to.
    */ 
  vtkSmartPointer<vtkRenderWindow> win;

  /** The interactor through which the layers can interact with the window.
    */ 
  vtkSmartPointer<vtkRenderWindowInteractor> interact;


  /** The camera used by all layers for this program.
    */
  vtkSmartPointer<vtkCamera> cam;

  /** This function sets some default properties on the vtkRenderWindow. Extracted to its' own function to keep the constructor from becoming cluttered.
    */ 
  void setWinProperties();

  /** This function sets up and connects a TimerCallbackCommand with the program.
    */ 
  void setupTimer();

  /** This function adds all interactors of each layer to the interactor/window
    */ 
  void setupInteractions();

  /** This function sets up the camera's associated movement callbacks..
    */ 
  void setupCameraCallback();

public:
  /** Constructor.
    */ 
  Program();

  /** This function adds a new layer (and thus vtkRenderer) to the program.
    * The layer is expected to set its own position in the vtkRenderWindow layer system.
    * @param layer : pointer to the layer to add.
    */ 
  void addLayer(Layer *layer);

  /** This function removes a given layer from the vtkRenderWindow and layers vector.
    * If the given layer is not actually in the program, nothing happens.
    * @param layer : the layer to removeLayer
    */
  void removeLayer(Layer *layer);

  /** This function updates the data for the associated layers to the given timestamp.
    * Also updates the renderWindow.
    * @param t : the timestamp to update the data to.
    */
  void updateData(int t);

  /**
   * This function renders the vtkRenderWindow for the first time.
   * Only call this function once!
   */
  void render();
};

#endif
