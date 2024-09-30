#ifndef USERSTUDYTIMER_H
#define USERSTUDYTIMER_H

#include <vtkCallbackCommand.h>
#include <fstream>
#include <chrono>

class UserStudyTimer : public vtkCallbackCommand {
public:
  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;

  static UserStudyTimer *New();
  UserStudyTimer();

  void setLogFilePath(std::string path);

private:
  std::ofstream logFile;
  std::chrono::steady_clock::time_point participantStartTime;
};


#endif //USERSTUDYTIMER_H
