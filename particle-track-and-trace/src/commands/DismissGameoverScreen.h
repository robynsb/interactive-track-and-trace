#ifndef DISMISSGAMEOVERSCREEN_H
#define DISMISSGAMEOVERSCREEN_H

#include <vtkCallbackCommand.h>
#include <functional>

class DismissGameoverScreen : public vtkCallbackCommand {
public:
  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;

  static DismissGameoverScreen *New();
  DismissGameoverScreen();

  void setDismiss(const std::function<void()> &dismiss);
private:
  std::function<void()> dismiss;
  explicit DismissGameoverScreen(std::function<void()> dismiss);
};


#endif //DISMISSGAMEOVERSCREEN_H
