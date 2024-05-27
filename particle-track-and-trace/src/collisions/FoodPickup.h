#ifndef FOODPICKUP_H
#define FOODPICKUP_H

#include "ParticleRemover.h"
#include "../layers/Health.h"

class FoodPickup : public ParticleRemover {
private:
  std::shared_ptr<Health> health;
public:
  FoodPickup(const vtkSmartPointer<vtkPoints> &particles, const std::shared_ptr<Health> &health);

public:
  void handleCollision(int index) const override;
};


#endif //FOODPICKUP_H
