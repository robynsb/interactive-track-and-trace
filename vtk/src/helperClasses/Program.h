#ifndef PROGRAM_H
#define PROGRAM_H

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "Layer.h"
#include "SpawnPointCallback.h"

class Program {
private:
  // Layer *background;
  // Layer *euler;
  // Layer *lagrange;

  std::vector<Layer *> layers;
  vtkSmartPointer<vtkRenderWindow> win;
  vtkSmartPointer<vtkRenderWindowInteractor> interact;

  void setWinProperties();
  void setupTimer();

public:
  Program();
  // Program(Layer *bg, Layer *e, Layer *l);

  void addLayer(Layer *layer);
  void removeLayer(Layer *layer);

  // void setBackground(Layer *bg);
  // void setEuler(Layer *e);
  // void setLagrange(Layer *l);
  void setLagrangeInteractor(SpawnPointCallback *cb);

  // void addInteractionStyle(vtkInteractorStyle style);
  void updateData(int t);

  void render();
};

#endif
