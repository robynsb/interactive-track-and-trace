#ifndef CHARACTERMOVECALLBACK_H
#define CHARACTERMOVECALLBACK_H

#include <memory>

#include <vtkDoubleArray.h>
#include <vtkCallbackCommand.h>


class CharacterMoveCallback : public vtkCallbackCommand {
  bool isAccelerating;
  bool isReversing;
  bool isGoingLeft;
  bool isGoingRight;
  void keyPressed(const std::string dir);
  void keyReleased(const std::string dir);

public:

  void Execute(vtkObject *caller, unsigned long eid, void *callData) override;
  static CharacterMoveCallback *New();

  bool getIsAccelerating() const;

  bool getIsReversing() const;

  bool getIsGoingLeft() const;

  bool getIsGoingRight() const;

  CharacterMoveCallback();
};


#endif //CHARACTERMOVECALLBACK_H
