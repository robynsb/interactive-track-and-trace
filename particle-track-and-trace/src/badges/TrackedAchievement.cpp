#include "TrackedAchievement.h"
#include <iostream>

bool TrackedAchievement::isAchieved() {
  bool achieved = achievement->isAchieved();
  badgeStatusSetter(achieved);
  return achieved;
}

TrackedAchievement::TrackedAchievement(std::unique_ptr<Achievement> achievement,
                                       const std::function<void(bool)> &badgeStatusSetter) :
                                       achievement(std::move(achievement)),
                                       badgeStatusSetter(badgeStatusSetter) {}
