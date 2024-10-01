#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include "Layer.h"
#include <memory>
#include "../statistics/Statistic.h"

class StatisticsManager : public Layer {
public:
  void handleGameOver() override;
  void addStatistic(std::shared_ptr<Statistic> statistic);
private:
  std::vector<std::shared_ptr<Statistic>> statistics;
};


#endif //STATISTICSMANAGER_H
