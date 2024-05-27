#ifndef HEALTH_H
#define HEALTH_H

#include "Layer.h"


class Health : public Layer {
private:
  double h = 0.18; // Original height of green bar.
  /**
   * Maximum health is 1.
   * Minimum health (i.e game over) is 0.
   */
  double health = 1;
  vtkSmartPointer<vtkTransform> healthBarScaler;
  void placeBackgroundHealth();
  void placeHealth();
public:
  void updateData(int t) override;
  void setHealth(double health);

  Health();
  void setCamera(vtkCamera *camera) override;
};


#endif //HEALTH_H
