#include "DebrisPickup.h"

void DebrisPickup::handleCollision(int index) const {
  ParticleRemover::handleCollision(index);
  health->changeHealth(-0.4);
  camera->shakeScreen();
}

DebrisPickup::DebrisPickup(const vtkSmartPointer<vtkPoints> &particles, const std::shared_ptr<Health> &health,
                           const std::shared_ptr<Camera> &camera)
        : ParticleRemover(particles), health(health), camera(camera) {}
