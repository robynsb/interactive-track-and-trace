#ifndef DUMMYCOLLISIONHANDLER_H
#define DUMMYCOLLISIONHANDLER_H


#include "ParticleCollisionCallback.h"

class DummyCollisionHandler : public ParticleCollisionCallback {
  void handleCollision(int index) const override;
};


#endif //DUMMYCOLLISIONHANDLER_H
