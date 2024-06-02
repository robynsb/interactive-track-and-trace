#ifndef PARTICLECOLLISION_H
#define PARTICLECOLLISION_H


#include <vtkPoints.h>
#include <memory.h>

#include "Layer.h"
#include "../collisions/ParticleCollisionCallback.h"

class ParticleCollision : public Layer {
public:
  ParticleCollision();
  void addPointSet(vtkSmartPointer<vtkPoints> points, const std::shared_ptr<ParticleCollisionCallback> &callback);

  void setDistance(double distance);

  void setPosition(vtkSmartPointer<vtkPoints> position);
  void updateData(int t) override;

private:
  std::vector<std::pair<vtkSmartPointer<vtkPoints>, std::shared_ptr<ParticleCollisionCallback>>> pointsets;
  vtkSmartPointer<vtkPoints> position;
  double distance;
  bool isInRange(double position[3], double point[3]);
};

#endif //PARTICLECOLLISION_H
