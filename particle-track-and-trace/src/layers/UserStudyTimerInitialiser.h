#ifndef USERSTUDYTIMERINITIALISER_H
#define USERSTUDYTIMERINITIALISER_H

#include "Layer.h"

class UserStudyTimerInitialiser : public Layer {
  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;
};


#endif //USERSTUDYTIMERINITIALISER_H
