#ifndef PARTICLECOLLISION_H
#define PARTICLECOLLISION_H


#include <vtkPoints.h>
#include <memory.h>
#include <memory>

#include "Layer.h"
#include "../collisions/ParticleCollisionCallback.h"

/**
 * Invisible layer that checks collisions every timestep between position and multiple sets of points.
 * You can define for every set of points a different callback to handle the collision.
 * Note this Layer shares the underlying data with a vtkSmartPointer,
 * therefore when the underlying data changes this will be seen in this layer.
 *
 * A collision is defined as the two points being less than the private member field distance apart.
 */
class ParticleCollision : public Layer {
public:
  /**
   * Constructor.
   */
  ParticleCollision();

  /**
   * Add a set of points and define their appropriate callback.
   * @param points The points to check collisions with position.
   * @param callback The callback to be called when position collides with one of the points.
   */
  void addPointSet(vtkSmartPointer<vtkPoints> points, const std::shared_ptr<ParticleCollisionCallback> &callback);

  /**
   * Set distance of collision.
   * @param distance distance of collision
   */
  void setDistance(double distance);

  /**
   * Set position that will be checked with the all the point sets.
   * @param position The position
   */
  void setPosition(vtkSmartPointer<vtkPoints> position);

  /**
   * Checks collision.
   */
  void updateData(int) override;

private:
  std::vector<std::pair<vtkSmartPointer<vtkPoints>, std::shared_ptr<ParticleCollisionCallback>>> pointsets;
  vtkSmartPointer<vtkPoints> position;
  double distance {0.2};
  bool isInRange(double position[3], double point[3]);
};

#endif //PARTICLECOLLISION_H
