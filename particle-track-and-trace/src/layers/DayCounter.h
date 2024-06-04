#ifndef DAYCOUNTER_H
#define DAYCOUNTER_H

#include <vtkTextActor.h>
#include "Layer.h"
#include "../statistics/Statistic.h"

class DayCounter : public Layer, public Statistic {
public:
  DayCounter();

  void handleGameOver() override;

  void updateData(int t) override;

  double getValue() const override;

private:
  double days {0};
  int lastT {0};
  vtkNew<vtkTextActor> text;
};


#endif //DAYCOUNTER_H
