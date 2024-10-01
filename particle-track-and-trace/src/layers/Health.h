#ifndef HEALTH_H
#define HEALTH_H

#include "Layer.h"
#include <memory>
#include "../gameovers/GameoverCallback.h"

class Health : public Layer {
private:
  static constexpr int gracePeriod = 10;;
  int graceProgress = 10;
  double h = 0.18; // Original height of green bar.
  double healthLossRate = 0.00075;
  /**
   * Maximum health is 1.
   * Minimum health (i.e game over) is 0.
   */
  double health = 1;
  vtkSmartPointer<vtkTransform> healthBarScaler;
  std::shared_ptr<GameoverCallback> gameoverCallback;
  void placeBackgroundHealth();
  void placeHealth();
  void setHealth(double health);
public:
  void updateData(int t) override;
  void changeHealth(double healthChange);
  void grace();

  Health(const std::shared_ptr<GameoverCallback> &gameoverCallback);
  void setCamera(vtkCamera *camera) override;

  void handleGameOver() override;
};


#endif //HEALTH_H
