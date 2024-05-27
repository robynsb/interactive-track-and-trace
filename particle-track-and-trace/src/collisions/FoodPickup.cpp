#include "FoodPickup.h"

void FoodPickup::handleCollision(int index) const {
  ParticleRemover::handleCollision(index);
  health->changeHealth(0.2);
}

FoodPickup::FoodPickup(const vtkSmartPointer<vtkPoints> &particles, const std::shared_ptr<Health> &health)
        : ParticleRemover(particles), health(health) {}
