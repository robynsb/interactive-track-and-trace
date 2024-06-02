#include "StatisticsManager.h"

void StatisticsManager::handleGameOver() {
  for(const auto &statistic : statistics) {
    statistic->resetStatistic();
  }
}

void StatisticsManager::addStatistic(std::shared_ptr<Statistic> statistic) {
  statistics.push_back(statistic);
}
