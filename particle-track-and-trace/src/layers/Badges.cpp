#include "Badges.h"

#include "../CartographicTransformation.h"

#include <vtkPolyData.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>

using namespace std;

Badges::Badges(string datapath) : pq{
        [](const BadgePair &lhs, const BadgePair &rhs) {
          return lhs.first > rhs.first; // For ascending order
        }} { }

Badges::Badges(const vector<std::pair<std::shared_ptr<Achievement>, std::shared_ptr<Badge>>> &badges) : badges(
        badges), pq{
        [](const BadgePair &lhs, const BadgePair &rhs) {
          return lhs.first > rhs.first; // For ascending order
        }} {
  for (auto &[achievement, badge] : badges) {
    ren->AddActor(badge->getActor());
  }
}

void Badges::setCamera(vtkCamera *camera) {
  getLayer()->SetActiveCamera(createNormalisedCamera());
}

void Badges::updateData(int t) {
  /**
   * Note: this code assumes that t doesn't reset. However this assumption is false.
   * It happens to be true as long as all awards end before the end of a year.
   * i.e the priority queue pq is empty at the beginning of each new year.
   */
  if (!pq.empty()) {
    auto [time, badge] = pq.top();
    if (time < t) {
      badge->setVisible(false);
      pq.pop();
    }
  }

  for (const auto& [achievement, badge] : badges) {
    if (!badge->isCollected() and achievement->isAchieved()) {
      collectBadge(t, badge);
    }
    badge->updateData(t);
  }
}

void Badges::handleGameOver() {
  for (const auto& [achievement, badge] : badges) {
    badge->reset();
  }
  while (!pq.empty()) {
    pq.pop();
  }
}

void Badges::collectBadge(int t, const std::shared_ptr<Badge>& badge) {
  badge->setVisible(true);
  badge->collect();
  pq.emplace(t + displaytime, badge);
}

void Badges::addBadge(const std::shared_ptr<Achievement>& achievement, const std::shared_ptr<Badge>& badge) {
  badges.emplace_back(achievement, badge);
  ren->AddActor(badge->getActor());
}
