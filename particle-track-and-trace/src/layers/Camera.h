#ifndef CAMERA_H
#define CAMERA_H

#include "Layer.h"

#include <random>

#define MAXSCREENSHAKE 0.005
#define MAXSCREENSHAKEDURATION 15
#define MAXZOOM 0.95
#define MAXZOOMDURATION 14
#define ZOOMLEVEL 0.4

class Camera : public Layer {
private:
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

  Camera();
};


#endif //CAMERA_H
