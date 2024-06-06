#ifndef CHARACTERMOUSEMOVECALLBACK_H
#define CHARACTERMOUSEMOVECALLBACK_H

#include <vtkCallbackCommand.h>
#include <vtkAbstractTransform.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>

class CharacterMouseMoveCallback : public vtkCallbackCommand {
public:
  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;
  static CharacterMouseMoveCallback *New();
  CharacterMouseMoveCallback();
  std::pair<double, double> getDesiredDisplayPos() const;
  bool isSteering() const;
private:
  std::pair<double, double> desiredDisplayPos {0,0};
  bool isClicking {false};
};


#endif //CHARACTERMOUSEMOVECALLBACK_H
