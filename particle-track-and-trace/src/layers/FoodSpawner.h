#ifndef FOODSPAWNER_H
#define FOODSPAWNER_H

#include <vtkPoints.h>
#include <vtkIntArray.h>
#include "Layer.h"

class FoodSpawner : public Layer {
private:
  static constexpr int numFoodSpawnPoints = 5;

  static constexpr double foodSpawnPoints[numFoodSpawnPoints][2] = {
          {2.916395032906174, 51.71082853247946},
          {0.9755257112715721, 50.68992153407205},
          {0.3046079210768962, 49.98644006769321},
          {4.665573557342298, 53.51461434416039},
          {-1.1091117082618904, 50.201646327208316}
  };

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
