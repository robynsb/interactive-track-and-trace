#ifndef TRACKEDCOLLISION_H
#define TRACKEDCOLLISION_H

#include "ParticleCollisionCallback.h"
#include "../statistics/Statistic.h"

#include <memory>

/**
 * TrackedCollision is a ParticleCollisionCallback that keeps a Statistic proportional to the number of collisions.
 *
 * This is a collision extension, this means it stores a callback itself that is run during handleCollision.
 */
class TrackedCollision : public ParticleCollisionCallback, public Statistic {
public:
  /**
   * Constructor.
   * @param increment The value to increment the statistic by after every collision.
   */
  TrackedCollision(double increment, const std::shared_ptr<ParticleCollisionCallback> &callback);

  /**
   * Call callback->handleCollision(index) and increments the Statistic.
   * @param index passed to callback.
   */
  void handleCollision(int index) override;

  /**
   * Gets the value of the statistic.
   */
  double getValue() const override;

  /**
   * Resets the statistic to 0. Called when game is over.
   */
  void resetStatistic() override;

private:
  double value {0};
  const double increment;
  std::shared_ptr<ParticleCollisionCallback> callback;
};

#endif //TRACKEDCOLLISION_H
