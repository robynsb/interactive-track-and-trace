#include "UserStudyTimerInitialiser.h"
#include "../commands/UserStudyTimer.h"

#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

void UserStudyTimerInitialiser::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
  vtkNew<UserStudyTimer> userStudyTimer;
  userStudyTimer->setLogFilePath("logs.csv");
  interactor->AddObserver(vtkCommand::KeyPressEvent, userStudyTimer);
}
