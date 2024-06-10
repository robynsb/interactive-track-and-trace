#ifndef BADGESACQUIRED_H
#define BADGESACQUIRED_H

#include "Statistic.h"

#include <vector>
#include <functional>

/**
 * BadgesAcquired is a statistic of how many achievements the player has achieved.
 */
class BadgesAcquired : public Statistic {
public:
  /**
   * Returns a function that the TrackedAchievement calls to broadcast the state of achievement.
   */
  std::function<void (bool)> getBadgeStatusSetter();

  /**
   * Counts the number of achievements that are achieved.
   */
  double getValue() const override;

  /**
   * Does nothing.
   */
  void resetStatistic() override;


private:
  std::vector<bool> acquiredBadges;

};


#endif //BADGESACQUIRED_H
