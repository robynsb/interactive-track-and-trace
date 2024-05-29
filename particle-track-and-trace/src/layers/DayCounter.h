#ifndef DAYCOUNTER_H
#define DAYCOUNTER_H

#include <vtkTextActor.h>
#include "Layer.h"

class DayCounter : public Layer {
private:
  double days = 0;
  int lastT = 0;
  vtkSmartPointer<vtkTextActor> text;
public:
  DayCounter();

  void handleGameOver() override;

  void updateData(int t) override;

};


#endif //DAYCOUNTER_H
