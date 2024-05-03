#ifndef PROGRAM_H
#define PROGRAM_H

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "Layer.h"
#include "SpawnPointCallback.h"

class Program {
private:
  Layer *background;
  Layer *euler;
  Layer *lagrange;
  vtkSmartPointer<vtkRenderWindow> win;
  vtkSmartPointer<vtkRenderWindowInteractor> interact;

  void setWinProperties();
  void setupTimer();

public:
  Program(Layer *bg, Layer *e, Layer *l);

  void setBackground(Layer *bg);
  void setEuler(Layer *e);
  void setLagrange(Layer *l);
  void setLagrangeInteractor(SpawnPointCallback *cb);

  // void addInteractionStyle(vtkInteractorStyle style);
  void updateData(int t);

  void render();
};

#endif
