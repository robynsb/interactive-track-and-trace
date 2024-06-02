#include "TrackedCollision.h"

TrackedCollision::TrackedCollision(double increment, const std::shared_ptr<ParticleCollisionCallback> &callback)
        : increment(increment), callback(callback) {}

double TrackedCollision::getValue() const {
  return value;
}

void TrackedCollision::handleCollision(int index) {
  value += increment;
  callback->handleCollision(index);
}

void TrackedCollision::resetStatistic() {
  value = 0;
}
