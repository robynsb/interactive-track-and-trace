#ifndef FOODSPAWNER_H
#define FOODSPAWNER_H

#include <vtkPoints.h>
#include <vtkIntArray.h>
#include "Layer.h"

class FoodSpawner : public Layer {
private:
  vtkSmartPointer<vtkPoints> food;
  vtkSmartPointer<vtkIntArray> particlesBeached;
  int foodPeriod = 1000000;
  int currentPeriodNumber = 0;
  bool shouldSpawnFood(int time);

public:
  FoodSpawner(vtkSmartPointer<vtkPoints> food, vtkSmartPointer<vtkIntArray> particlesBeached);

public:
  void updateData(int t) override;
};


#endif //FOODSPAWNER_H
