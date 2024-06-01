#include "ParticleRemover.h"

void ParticleRemover::handleCollision(int index) const {
  double removalZone[] = {13.875, 62.625, 0};
  particles->SetPoint(index, removalZone);
  particles->Modified();
}

ParticleRemover::ParticleRemover(const vtkSmartPointer<vtkPoints> &particles) : particles(particles) {}
