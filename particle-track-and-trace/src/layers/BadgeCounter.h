#ifndef BADGECOUNTER_H
#define BADGECOUNTER_H

#include "Layer.h"

#include "../statistics/Statistic.h"

#include <vtkTextActor.h>

class BadgeCounter : public Layer {
public:
  explicit BadgeCounter(const std::shared_ptr<Statistic> &acquiredBadgeStatistic);

  void updateData(int t) override;

private:
  vtkNew<vtkTextActor> text;
  std::shared_ptr<Statistic> acquiredBadgeStatistic;

};


#endif //BADGECOUNTER_H
