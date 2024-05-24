#ifndef PARTICLEREMOVER_H
#define PARTICLEREMOVER_H

#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include "ParticleCollisionCallback.h"

class ParticleRemover : public ParticleCollisionCallback {
  vtkSmartPointer<vtkPoints> particles;
public:
  explicit ParticleRemover(const vtkSmartPointer<vtkPoints> &particles);

  void handleCollision(int index) const override;
};


#endif //PARTICLEREMOVER_H
