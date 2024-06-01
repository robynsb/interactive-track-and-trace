#ifndef CAMERA_H
#define CAMERA_H

#include "Layer.h"

#include <random>

class Camera : public Layer {
private:
  static constexpr double maxScreenShake = 0.005;
  static constexpr double maxScreenShakeDuration = 15;
  static constexpr double maxZoom = 0.95;
  static constexpr int maxZoomDuration = 14;
  static constexpr double zoomLevel = 0.4;

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  int screenShakeProgress = 0;
  int zoomProgress = 0;
  bool zoomIn = false;
  double getScreenShakeOffset();
  double getZoomOffset();
public:
  void clampCamera(double pos[3]);
  void updateData(int t) override;
  void shakeScreen();
  void zoomScreen();

  void handleGameOver() override;

  Camera();
};


#endif //CAMERA_H
