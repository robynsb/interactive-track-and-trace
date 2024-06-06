#ifndef BADGES_H
#define BADGES_H

#include "Layer.h"

#include "../badges/Badge.h"
#include "../badges/Achievement.h"

#include <queue>

class Badges : public Layer {
public:
  Badges(std::string datapath);

  explicit Badges(const std::vector<std::pair<std::shared_ptr<Achievement>, std::shared_ptr<Badge>>> &badges);

  void addBadge(const std::shared_ptr<Achievement>& achievement, const std::shared_ptr<Badge>& badge);

  void updateData(int t) override;

  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;
private:
  static constexpr int displaytime {2330000};
  std::vector<std::pair<std::shared_ptr<Achievement>, std::shared_ptr<Badge>>> badges;
  using BadgePair = std::pair<int, std::shared_ptr<Badge>>;
  using Comparator = std::function<bool(const BadgePair&, const BadgePair&)>;
  using PriorityQueue = std::priority_queue<BadgePair, std::vector<BadgePair>, Comparator>;
  PriorityQueue pq;

  void collectBadge(int t, const std::shared_ptr<Badge>& badge);

};


#endif //BADGES_H
