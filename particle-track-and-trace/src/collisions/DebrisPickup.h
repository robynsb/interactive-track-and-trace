#ifndef DEBRISPICKUP_H
#define DEBRISPICKUP_H

#include "ParticleRemover.h"
#include "../layers/Health.h"
#include "../layers/Camera.h"
#include "../layers/Badges.h"

/**
 * DebrisPickup is ParticleCollisionCallback for when debris is picked up.
 */
class DebrisPickup : public ParticleRemover {
public:
  /**
   * Constructor.
   * @param particles to be removed from.
   * @param health that will be affected.
   * @param camera that will be shook.
   */
  DebrisPickup(
          const vtkSmartPointer<vtkPoints> &particles,
          const std::shared_ptr<Health> &health,
          const std::shared_ptr<Camera> &camera
  );

  /**
   * Has the following effects:
   * - Decrease health.
   * - Get a small grace period.
   * - Shakes screens.
   * - Removes particle that was collided with.
   */
  void handleCollision(int index) override;
private:
  std::shared_ptr<Health> health;
  std::shared_ptr<Camera> camera;
};


#endif //DEBRISPICKUP_H
