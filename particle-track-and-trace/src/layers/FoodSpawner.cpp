#include "FoodSpawner.h"

#include <utility>

#define NUMFOODSPAWNPOINTS 5

double foodSpawnPoints[NUMFOODSPAWNPOINTS][2] = {
        {2.916395032906174, 51.71082853247946},
        {0.9755257112715721, 50.68992153407205},
        {0.3046079210768962, 49.98644006769321},
        {4.665573557342298, 53.51461434416039},
        {-1.1091117082618904, 50.201646327208316}
};

bool FoodSpawner::shouldSpawnFood(int time) {
  bool isNewPeriod = time / foodPeriod != currentPeriodNumber;
  currentPeriodNumber = time / foodPeriod;
  return isNewPeriod;
}

void FoodSpawner::updateData(int t) {
  if(shouldSpawnFood(t)) {
    double *point = foodSpawnPoints[currentPeriodNumber % NUMFOODSPAWNPOINTS];
    food->InsertNextPoint(point[0], point[1], 0);
    food->Modified();
    particlesBeached->InsertNextValue(0);
    particlesBeached->Modified();
  }
}

FoodSpawner::FoodSpawner(vtkSmartPointer<vtkPoints> food, vtkSmartPointer<vtkIntArray> particlesBeached)
        : food(food), particlesBeached(particlesBeached) {}
