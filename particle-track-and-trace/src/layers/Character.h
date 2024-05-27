#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkTransform.h>
#include <vtkGlyphSource2D.h>
#include "Layer.h"
#include "Camera.h"
#include "../commands/CharacterMoveCallback.h"
#include "../advection/UVGrid.h"

#define ROTATIONSTEP 0.1
#define ACCELERATESTEP 0.05
#define DECELLERATION 0.05
#define MAXVELOCITY 0.02
#define SCALEHORIZONTALVELOCITY 1.6 // Since the velocity is measured in degrees per time step,
                                    // and the longitudanal lines on our map are "squished" more
                                    // than latitudanal lines. This scaling factor corrects for this
                                    // to make the character "look" like they move the same velocity
                                    // horizontally vs vertically.

class Character : public Layer {
private:
  vtkSmartPointer<vtkPoints> position;
  vtkSmartPointer<vtkPolyData> data;
  vtkSmartPointer<CharacterMoveCallback> controller;
  vtkSmartPointer<vtkAbstractTransform> cameraTransform;
  vtkSmartPointer<vtkTransform> rotater;
  std::shared_ptr<UVGrid> uvGrid;
  std::shared_ptr<Camera> camera;

  double velocity = 0;
  double throttle = 0;
  double angleRadians = 0;
  void updateDirection();
  void updateVelocity();
  void updatePosition();

public:
  Character(std::shared_ptr<UVGrid> uvGrid, std::string path, std::shared_ptr<Camera> camera);
  void updateData(int t) override;

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  vtkSmartPointer<vtkPoints> getPosition();
};


#endif //CHARACTER_H
