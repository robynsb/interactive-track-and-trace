#ifndef BADGES_H
#define BADGES_H

#include "Layer.h"
#include "../badges/Badge.h"
#include <queue>


class Badges : public Layer {
private:
  static constexpr int displaytime {2000000};
  double gramsOfDebrisEaten {0};
  double gramsOfFoodEaten {0};
  std::shared_ptr<Badge> medianIsKing;
  std::shared_ptr<Badge> northernFulmar;
  std::shared_ptr<Badge> firstSteps;
  std::shared_ptr<Badge> everyoneMakesMistakes;
  std::vector<std::shared_ptr<Badge>> badges;
  using BadgePair = std::pair<int, std::shared_ptr<Badge>>;
  using Comparator = std::function<bool(const BadgePair&, const BadgePair&)>;
  using PriorityQueue = std::priority_queue<BadgePair, std::vector<BadgePair>, Comparator>;
  PriorityQueue pq;

  void collectBadge(int t, std::shared_ptr<Badge> badge);
public:
  Badges(std::string datapath);

  void logDebrisConsumption();

  void logFoodConsumption();

  void updateData(int t) override;

  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;

};


#endif //BADGES_H
