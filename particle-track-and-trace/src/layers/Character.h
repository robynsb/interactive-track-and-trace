#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkTransform.h>
#include <vtkGlyphSource2D.h>
#include "Layer.h"
#include "../commands/CharacterMoveCallback.h"
#include "../advection/UVGrid.h"

#define ROTATIONSTEP 0.1
#define ACCELERATESTEP 0.05
#define DECELLERATION 0.1
#define MAXVELOCITY 0.01

class Character : public Layer {
private:
  vtkSmartPointer<vtkPoints> position; // TODO: Make this position in latlon instead of normalised coords
  vtkSmartPointer<vtkPolyData> data;
  vtkSmartPointer<vtkDoubleArray> direction;
  vtkSmartPointer<CharacterMoveCallback> controller;
  vtkSmartPointer<vtkAbstractTransform> cameraTransform;
  vtkSmartPointer<vtkGlyphSource2D> arrowSource;

  double velocity = 0;
  double throttle = 0;
  double angleRadians = 0;
  void updateDirection();
  void updateVelocity();
  void updatePosition();
  void clampCamera(double pos[3]);

public:

  Character(std::shared_ptr<UVGrid> uvGrid);
  void updateData(int t) override;

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  vtkSmartPointer<vtkPoints> getPosition();
};


#endif //CHARACTER_H
