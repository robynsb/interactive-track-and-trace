#ifndef PROGRAM_H
#define PROGRAM_H

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "Layer.h"
#include "SpawnPointCallback.h"

class Program {
private:
  std::vector<Layer *> layers;
  vtkSmartPointer<vtkRenderWindow> win;
  vtkSmartPointer<vtkRenderWindowInteractor> interact;

  void setWinProperties();
  void setupTimer();

public:
  Program();

  void addLayer(Layer *layer);
  void removeLayer(Layer *layer);

  void setLagrangeInteractor(SpawnPointCallback *cb);

  void updateData(int t);

  void render();
};

#endif
