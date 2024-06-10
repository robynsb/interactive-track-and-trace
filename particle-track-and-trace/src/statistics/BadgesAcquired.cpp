#include "BadgesAcquired.h"

double BadgesAcquired::getValue() const {
  int number = 0;
  for (bool badgeStatus : acquiredBadges) {
    if (badgeStatus) {
      number++;
    }
  }
  return number;
}

void BadgesAcquired::resetStatistic() {
  // Do nothing.
}

std::function<void(bool)> BadgesAcquired::getBadgeStatusSetter() {
  size_t n = acquiredBadges.size();
  acquiredBadges.push_back(false);
  return [=, this](bool achieved) { acquiredBadges[n] = achieved; };
}