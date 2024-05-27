#ifndef CAMERA_H
#define CAMERA_H

#include "Layer.h"

#include <random>

#define MAXSCREENSHAKE 0.005
#define MAXSCREENSHAKEDURATION 15

class Camera : public Layer {
private:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  int screenShakeProgress = 0;
  double getScreenShakeOffset();
public:
  void clampCamera(double pos[3]);
  void updateData(int t) override;
  void shakeScreen();

  Camera();
};


#endif //CAMERA_H
