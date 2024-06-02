#include "DebrisPickup.h"

void DebrisPickup::handleCollision(int index) {
  ParticleRemover::handleCollision(index);
  camera->shakeScreen();
  health->changeHealth(-0.3);
  health->grace();
}

DebrisPickup::DebrisPickup(
        const vtkSmartPointer<vtkPoints> &particles,
        const std::shared_ptr<Health> &health,
        const std::shared_ptr<Camera> &camera
)
        : ParticleRemover(particles), health(health), camera(camera) {}
