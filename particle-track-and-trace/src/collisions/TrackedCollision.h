#ifndef TRACKEDCOLLISION_H
#define TRACKEDCOLLISION_H

#include "ParticleCollisionCallback.h"
#include "../badges/Statistic.h"

#include <memory>

class TrackedCollision : public ParticleCollisionCallback, public Statistic {
public:
  TrackedCollision(double increment, const std::shared_ptr<ParticleCollisionCallback> &callback);
  void handleCollision(int index) override;
  double getValue() const override;

  void resetStatistic() override;

private:
  double value {0};
  const double increment;
  std::shared_ptr<ParticleCollisionCallback> callback;
};

#endif //TRACKEDCOLLISION_H
