#ifndef DUMMYCOLLISIONHANDLER_H
#define DUMMYCOLLISIONHANDLER_H


#include "ParticleCollisionCallback.h"

/**
 * Dummy collision to test collisions.
 */
class DummyCollisionHandler : public ParticleCollisionCallback {
  /**
   * Prints a message to standard out.
   */
  void handleCollision(int index) override;
};


#endif //DUMMYCOLLISIONHANDLER_H
