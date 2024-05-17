#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include "Layer.h"
#include "../commands/CharacterMoveCallback.h"

#define ROTATIONSTEP 0.1
#define ACCELERATESTEP 0.05
#define DECELLERATION 0.1
#define MAXVELOCITY 0.005

class Character : public Layer {
private:
  vtkSmartPointer<vtkPoints> position; // TODO: Make this position in latlon instead of normalised coords
  vtkSmartPointer<vtkPolyData> data;
  vtkSmartPointer<vtkDoubleArray> direction;
  vtkSmartPointer<CharacterMoveCallback> controller;

  double velocity = 0;
  double throttle = 0;
  double angleRadians = 0;
  void updateDirection();
  void updateVelocity();
  void updatePosition();
  void clampCamera(double pos[3]);

public:

  Character();
  void updateData(int t) override;

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  vtkSmartPointer<vtkPoints> getPosition();
};


#endif //CHARACTER_H
