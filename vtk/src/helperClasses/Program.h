#ifndef PROGRAM_H
#define PROGRAM_H

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "Layer.h"

class Program {
private:
  Layer *background;
  Layer *euler;
  Layer *lagrange;
  vtkSmartPointer<vtkRenderWindow> win;
  vtkSmartPointer<vtkRenderWindowInteractor> interact;

  void setWinProperties();
  static void CallbackFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
  void setupTimer();

public:
  Program(Layer *bg, Layer *e, Layer *l);

  void setBackground(Layer *bg);
  void setEuler(Layer *e);
  void setLagrange(Layer *l);

  // void addInteractionStyle(vtkInteractorStyle style);

  void render();
};

#endif
