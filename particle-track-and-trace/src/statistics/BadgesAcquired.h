#ifndef BADGESACQUIRED_H
#define BADGESACQUIRED_H

#include "Statistic.h"

#include <vector>
#include <functional>

class BadgesAcquired : public Statistic {
public:
  double getValue() const override;

  void resetStatistic() override;

  std::function<void (bool)> getBadgeStatusSetter();

private:
  std::vector<bool> acquiredBadges;

};


#endif //BADGESACQUIRED_H
