#ifndef PARTICLECOLLISIONCALLBACK_H
#define PARTICLECOLLISIONCALLBACK_H

class ParticleCollisionCallback {
public:
  virtual void handleCollision(int index) const = 0;

  virtual ~ParticleCollisionCallback() = default;
};

#endif //PARTICLECOLLISIONCALLBACK_H
