#include <vtkRenderWindowInteractor.h>
#include "UserStudyTimer.h"

void UserStudyTimer::Execute(vtkObject *caller, unsigned long eid, void *callData) {
  auto intr = reinterpret_cast<vtkRenderWindowInteractor *>(caller);
  if(eid == vtkCommand::KeyPressEvent) {
    if(strcmp(intr->GetKeySym(), "k") == 0) {
      // Start timer
      participantStartTime = std::chrono::steady_clock::now();
      std::cout << "Timer started!\n";
    }
    if(strcmp(intr->GetKeySym(), "l") == 0) {
      // Stop timer and save time
      auto now = std::chrono::steady_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - participantStartTime);
      logFile << duration << endl;
      std::cout << "Timer stopped and saved a time of " << duration << " seconds!\n";

    }
  }
}

void UserStudyTimer::setLogFilePath(std::string path) {
  logFile.open(path, ios::app);
}

UserStudyTimer::UserStudyTimer() {}

UserStudyTimer *UserStudyTimer::New() {
  return new UserStudyTimer;
}
