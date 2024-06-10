#ifndef PARTICLECOLLISIONCALLBACK_H
#define PARTICLECOLLISIONCALLBACK_H

/**
 * Decides what should happen when a collision happens.
 * Typically this will be between a particle and player.
 * Used by the ParticleCollision layer.
 */
class ParticleCollisionCallback {
public:
  /**
   * Function to implement collision logic.
   * @param index The index of the particle that was collided with in its corresponding point set.
   * Note: That there can be multiple particles with the same index if they
   * come from different sets. See ParticleCollision layer for more details.
   */
  virtual void handleCollision(int index) = 0;

  virtual ~ParticleCollisionCallback() = default;
};

#endif //PARTICLECOLLISIONCALLBACK_H
