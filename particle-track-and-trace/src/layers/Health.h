#ifndef HEALTH_H
#define HEALTH_H

#include "Layer.h"

#define GRADEPERIOD 10;

class Health : public Layer {
private:
  int gracePeriod = 10;
  double h = 0.18; // Original height of green bar.
  double healthLossRate = 0.0005;
  /**
   * Maximum health is 1.
   * Minimum health (i.e game over) is 0.
   */
  double health = 1;
  vtkSmartPointer<vtkTransform> healthBarScaler;
  void placeBackgroundHealth();
  void placeHealth();
  void setHealth(double health);
public:
  void updateData(int t) override;
  void changeHealth(double healthChange);

  Health();
  void setCamera(vtkCamera *camera) override;
};


#endif //HEALTH_H
