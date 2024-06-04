#ifndef SIMPLEACHIEVEMENT_H
#define SIMPLEACHIEVEMENT_H

#include "Achievement.h"
#include "../statistics/Statistic.h"

#include <memory>

class SimpleAchievement : public Achievement {
public:
  SimpleAchievement(const std::shared_ptr<Statistic> &statistic, double requiredValue);

  bool isAchieved() override;
private:
  std::shared_ptr<Statistic> statistic;
  double requiredValue;

};

#endif //SIMPLEACHIEVEMENT_H
