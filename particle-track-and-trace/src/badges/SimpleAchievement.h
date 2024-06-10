#ifndef SIMPLEACHIEVEMENT_H
#define SIMPLEACHIEVEMENT_H

#include "Achievement.h"
#include "../statistics/Statistic.h"

#include <memory>

/**
 * A SimpleAchievement is achieved when the inputted statistic is greater than some constant requiredValue.
 */
class SimpleAchievement : public Achievement {
public:
  /**
   * Constructor.
   * @param statistic to evaluate.
   * @param requiredValue to compare with statistic value.
   */
  SimpleAchievement(const std::shared_ptr<Statistic> &statistic, double requiredValue);

  bool isAchieved() override;
private:
  std::shared_ptr<Statistic> statistic;
  double requiredValue;

};

#endif //SIMPLEACHIEVEMENT_H
