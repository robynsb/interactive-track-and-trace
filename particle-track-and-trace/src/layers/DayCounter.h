#ifndef DAYCOUNTER_H
#define DAYCOUNTER_H

#include <vtkTextActor.h>
#include "Layer.h"
#include "../badges/Statistic.h"

class DayCounter : public Layer, public Statistic {
private:
  double days {0};
  int lastT {0};
  vtkNew<vtkTextActor> text;
public:
  DayCounter();

  void handleGameOver() override;

  void updateData(int t) override;

  double getValue() const override;
};


#endif //DAYCOUNTER_H
