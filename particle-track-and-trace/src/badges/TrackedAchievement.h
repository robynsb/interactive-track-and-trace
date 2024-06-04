#ifndef TRACKEDACHIEVEMENT_H
#define TRACKEDACHIEVEMENT_H

#include "Achievement.h"
#include "../statistics/BadgesAcquired.h"

#include <memory>

class TrackedAchievement : public Achievement {
public:
  TrackedAchievement(std::unique_ptr<Achievement> achievement,
                     const std::function<void(bool)> &badgeStatusSetter);

  bool isAchieved() override;

private:
  std::unique_ptr<Achievement> achievement;
  std::function<void (bool)> badgeStatusSetter;
};


#endif //TRACKEDACHIEVEMENT_H
