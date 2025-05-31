#ifndef DISPLAYEulerCOMMAND_H
#define DISPLAYEulerCOMMAND_H

#include <vtkCallbackCommand.h>
#include <functional>

class DisplayEulerCommand :public vtkCallbackCommand {

public:
  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;

  static DisplayEulerCommand *New();
  DisplayEulerCommand();

  void setToggle(const std::function<void()> &toggle);
private:
  std::function<void()> toggle;
  explicit DisplayEulerCommand(std::function<void()> toggle);
};


#endif //DISPLAYEulerCOMMAND_H
