#include "FoodSpawner.h"

#include <utility>

bool FoodSpawner::shouldSpawnFood(int time) {
  bool isNewPeriod = time / foodPeriod != currentPeriodNumber;
  currentPeriodNumber = time / foodPeriod;
  return isNewPeriod;
}

void FoodSpawner::updateData(int t) {
  if(shouldSpawnFood(t)) {
    const double *point = foodSpawnPoints[currentPeriodNumber % numFoodSpawnPoints];
    food->InsertNextPoint(point[0], point[1], 0);
    food->Modified();
    particlesBeached->InsertNextValue(0);
    particlesBeached->Modified();
  }
}

FoodSpawner::FoodSpawner(vtkSmartPointer<vtkPoints> food, vtkSmartPointer<vtkIntArray> particlesBeached)
        : food(food), particlesBeached(particlesBeached) {}
