#include "SimpleAchievement.h"

bool SimpleAchievement::isAchieved() {
  return statistic->getValue() > requiredValue;
}

SimpleAchievement::SimpleAchievement(const std::shared_ptr<Statistic> &statistic, double requiredValue) : statistic(
        statistic), requiredValue(requiredValue) {}
