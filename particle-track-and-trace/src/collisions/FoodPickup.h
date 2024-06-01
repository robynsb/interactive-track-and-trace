#ifndef FOODPICKUP_H
#define FOODPICKUP_H

#include "ParticleRemover.h"
#include "../layers/Health.h"
#include "../layers/Camera.h"
#include "../layers/Character.h"
#include "../layers/Badges.h"

class FoodPickup : public ParticleRemover {
private:
  std::shared_ptr<Health> health;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Character> character;
  std::shared_ptr<Badges> badges;
public:
  FoodPickup(const vtkSmartPointer<vtkPoints> &particles,
             const std::shared_ptr<Health> &health,
             const std::shared_ptr<Camera> &camera,
             const std::shared_ptr<Character> &character,
             const std::shared_ptr<Badges> &badges
             );

public:
  void handleCollision(int index) const override;
};


#endif //FOODPICKUP_H
