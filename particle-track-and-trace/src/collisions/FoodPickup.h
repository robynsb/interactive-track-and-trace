#ifndef FOODPICKUP_H
#define FOODPICKUP_H

#include "ParticleRemover.h"
#include "../layers/Health.h"
#include "../layers/Camera.h"
#include "../layers/CharacterNoStop.h"
#include "../layers/Badges.h"

/**
 * FoodPickup is a ParticleCollisionCallback for when food is picked up.
 */
class FoodPickup : public ParticleRemover {
public:
  /**
   * Constuctor.
   * @param particles Particles to remove from.
   * @param health Health that will be changed.
   * @param camera Camera that will be zoomed in.
   * @param character Character that has the speed increased.
   */
  FoodPickup(const vtkSmartPointer<vtkPoints> &particles,
             const std::shared_ptr<Health> &health,
             const std::shared_ptr<Camera> &camera,
             const std::shared_ptr<CharacterNoStop> &character
  );

  /**
   * Has the following effects:
   * - Removes particle that was collided with.
   * - Increases health.
   * - Zooms particle temporarily.
   * - Increases character speed temporarily.
   */
  void handleCollision(int index) override;
private:
  std::shared_ptr<Health> health;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<CharacterNoStop> character;
};


#endif //FOODPICKUP_H
