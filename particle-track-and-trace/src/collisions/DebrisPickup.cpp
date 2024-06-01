#include "DebrisPickup.h"

void DebrisPickup::handleCollision(int index) const {
  ParticleRemover::handleCollision(index);
  camera->shakeScreen();
  badges->logDebrisConsumption();
  health->changeHealth(-0.3);
  health->grace();
}

DebrisPickup::DebrisPickup(
        const vtkSmartPointer<vtkPoints> &particles,
        const std::shared_ptr<Health> &health,
        const std::shared_ptr<Camera> &camera,
        const std::shared_ptr<Badges> &badges
)
        : ParticleRemover(particles), health(health), camera(camera), badges(badges) {}
