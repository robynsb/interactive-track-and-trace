#ifndef PARTICLEREMOVER_H
#define PARTICLEREMOVER_H

#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include "ParticleCollisionCallback.h"

/**
 * ParticleRemover is a ParticleCollisionCallback that removes a particle from the game when
 * it is collided with.
 */
class ParticleRemover : public ParticleCollisionCallback {
public:
  /**
   * Constructor.
   * @param particles The particle set it will remove the points from
   */
  explicit ParticleRemover(const vtkSmartPointer<vtkPoints> &particles);

  /**
   * Remove remove particle particles[index].
   * @param index Index of particle to remove from particles.
   */
  void handleCollision(int index) override;
private:
  vtkSmartPointer<vtkPoints> particles;
};


#endif //PARTICLEREMOVER_H
