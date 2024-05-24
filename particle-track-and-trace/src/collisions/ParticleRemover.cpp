#include "ParticleRemover.h"

void ParticleRemover::handleCollision(int index) const {
  double removalZone[] = {12.875, 62.625, 0};
  particles->SetPoint(index, removalZone);
}

ParticleRemover::ParticleRemover(const vtkSmartPointer<vtkPoints> &particles) : particles(particles) {}
