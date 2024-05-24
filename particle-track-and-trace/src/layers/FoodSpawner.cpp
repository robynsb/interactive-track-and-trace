#include "FoodSpawner.h"

#include <utility>

#define NUMFOODSPAWNPOINTS 5

double foodSpawnPoints[NUMFOODSPAWNPOINTS][2] = {
        {1.1588076146811954, 51.605932500045014},
        {4.526760789202001, 53.02657003258698},
        {2.9450064711258626, 53.815262103281114},
        {2.3531936077173423, 51.405004957704065},
        {7.302901029118159, 55.75080719781954}
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
