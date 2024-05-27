#ifndef TIMER_H
#define TIMER_H

#include "Layer.h"
#include "../Program.h"

class Timer : public Layer {
private:
  std::shared_ptr<Program> program;
  int dt;
public:
  Timer(const std::shared_ptr<Program> &program, int dt);

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;
};


#endif //TIMER_H
