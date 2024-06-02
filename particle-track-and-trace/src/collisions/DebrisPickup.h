#ifndef DEBRISPICKUP_H
#define DEBRISPICKUP_H

#include "ParticleRemover.h"
#include "../layers/Health.h"
#include "../layers/Camera.h"
#include "../layers/Badges.h"

class DebrisPickup : public ParticleRemover {
private:
  std::shared_ptr<Health> health;
  std::shared_ptr<Camera> camera;
public:
  DebrisPickup(
          const vtkSmartPointer<vtkPoints> &particles,
          const std::shared_ptr<Health> &health,
          const std::shared_ptr<Camera> &camera
  );

public:
  void handleCollision(int index) override;
};


#endif //DEBRISPICKUP_H
