#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkTransform.h>
#include <vtkGlyphSource2D.h>
#include <vtkTexture.h>

#include "Layer.h"
#include "Camera.h"
#include "../commands/CharacterMoveCallback.h"
#include "../advection/UVGrid.h"

class Character : public Layer {
private:
  static constexpr double rotationStep = 0.1;
  static constexpr double accelerateStep = 0.05;
  static constexpr double decelleration = 0.05;
  static constexpr double maxVelocity = 0.02;
  static constexpr double scaleHorizontalVelocity = 1.6; // Since the velocity is measured in degrees per time step,
  // and the longitudanal lines on our map are "squished" more
  // than latitudanal lines. This scaling factor corrects for this
  // to make the character "look" like they move the same velocity
  // horizontally vs vertically.
  static constexpr double dashVelocityBonus = 0.04;
  static constexpr int dashDuration = 15;
  static constexpr double startLon = 6.513089433595266; // Groningen
  static constexpr double startLat = 53.44059997086552;

  vtkNew<vtkTexture> texture;
  vtkNew<vtkActor> texturedPlane;
  vtkNew<vtkPoints> position;
  vtkNew<vtkPolyData> data;
  vtkNew<CharacterMoveCallback> controller;
  vtkSmartPointer<vtkAbstractTransform> cameraTransform;
  vtkNew<vtkTransform> rotater;
  std::shared_ptr<UVGrid> uvGrid;
  std::shared_ptr<Camera> camera;

  double velocity = 0;
  double throttle = 0;
  double angleRadians = 0;
  int dashProgress = 0;
  bool dashing = false;
  void updateDirection();
  void updateVelocity();
  void updatePosition();
  double getDashVelocityBonus();
  void updateDashProgress();

public:
  Character(std::shared_ptr<UVGrid> uvGrid, std::string path, std::shared_ptr<Camera> camera);
  void updateData(int t) override;

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void handleGameOver() override;

  void dash();

  vtkSmartPointer<vtkPoints> getPosition();
};


#endif //CHARACTER_H
