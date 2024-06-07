#ifndef DISPLAYSPLASHSCREENCOMMAND_H
#define DISPLAYSPLASHSCREENCOMMAND_H

#include <vtkCallbackCommand.h>
#include <functional>

class DisplaySplashScreenCommand :public vtkCallbackCommand {

public:
  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;

  static DisplaySplashScreenCommand *New();
  DisplaySplashScreenCommand();

  void setToggle(const std::function<void()> &toggle);
private:
  std::function<void()> toggle;
  explicit DisplaySplashScreenCommand(std::function<void()> toggle);
};


#endif //DISPLAYSPLASHSCREENCOMMAND_H
