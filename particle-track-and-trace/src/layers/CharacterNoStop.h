#ifndef CHARACTERNOSTOP_H
#define CHARACTERNOSTOP_H

#include <memory>

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDoubleArray.h>
#include <vtkTransform.h>
#include <vtkGlyphSource2D.h>
#include <vtkTexture.h>

#include "Layer.h"
#include "Camera.h"
#include "../commands/CharacterMouseMoveCallback.h"
#include "../advection/UVGrid.h"

class CharacterNoStop : public Layer {

public:
  CharacterNoStop(std::shared_ptr<UVGrid> uvGrid, std::string path, std::shared_ptr<Camera> camera);
  void updateData(int t) override;

  void addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) override;

  void handleGameOver() override;

  void dash();

  vtkSmartPointer<vtkPoints> getPosition();

private:
  static constexpr double rotationStep = 0.1;
  static constexpr double maxVelocity = 0.02;
  static constexpr double scaleHorizontalVelocity = 1.6; // Since the velocity is measured in degrees per time step,
  // and the longitudanal lines on our map are "squished" more
  // than latitudanal lines. This scaling factor corrects for this
  // to make the character "look" like they move the same velocity
  // horizontally vs vertically.
  static constexpr double dashVelocityBonus = 0.04;
  static constexpr int dashDuration = 30;
  static constexpr double startLon = 6.513089433595266; // Groningen
  static constexpr double startLat = 53.44059997086552;

  vtkNew<vtkTexture> texture;
  vtkNew<vtkActor> texturedPlane;
  vtkNew<vtkPoints> position;
  vtkNew<vtkPolyData> data;
  vtkNew<CharacterMouseMoveCallback> controller;
  vtkSmartPointer<vtkAbstractTransform> cameraTransform;
  vtkNew<vtkTransform> rotater;
  std::shared_ptr<UVGrid> uvGrid;
  std::shared_ptr<Camera> camera;
  bool clickingNecessaryForSteering = false;

  double velocity {maxVelocity};
  double angleRadians {0};
  int dashProgress {0};
  bool dashing = false;
  void updateAngle();
  void updateDirection();
  void updatePosition();
  void updateVelocity();
  double getDashVelocityBonus();
  void updateDashProgress();
  double getDesiredAngle();
};


#endif //CHARACTERNOSTOP_H
