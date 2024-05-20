#include "ParticleCollision.h"

using namespace std;

ParticleCollision::ParticleCollision(): distance(10) {}

void ParticleCollision::addPointSet(
        vtkSmartPointer<vtkPoints> points,
        unique_ptr<ParticleCollisionCallback> callback
) {
  pair<vtkSmartPointer<vtkPoints>, unique_ptr<ParticleCollisionCallback>> pointset = {points, std::move(callback)};
  pointsets.push_back(std::move(pointset));
}

bool ParticleCollision::isInRange(double pos[3], double point[3]) {
  double x = pos[0]-point[0];
  double y = pos[1]-point[1];
  return x*x + y*y < distance*distance;
}

void ParticleCollision::updateData(int t) {
  double pos[3];
  position->GetPoint(0, pos);
  for (auto&& [points, cb] : pointsets) {
    for (int i = 0; i < points->GetNumberOfPoints(); i++) {
      double point[3];
      points->GetPoint(i, point);
      if(isInRange(pos, point)) {
        cb->handleCollision(i);
      }
    }
  }
}

void ParticleCollision::setPosition(vtkSmartPointer<vtkPoints> position) {
  this->position = position;
}

void ParticleCollision::setDistance(double distance) {
  this->distance = distance;
}
