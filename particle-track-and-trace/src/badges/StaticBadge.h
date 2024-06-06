#ifndef STATICBADGE_H
#define STATICBADGE_H

#include "Badge.h"
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>

class StaticBadge : public Badge {
private:
  static constexpr double initY = 1.5;
  static constexpr double targetY = 0.85;
  static constexpr double fadeOutIn = 2; // seconds
  std::string datapath;
  vtkNew<vtkPoints> position;
  vtkNew<vtkActor> texturedPlane;
  bool moving = false;
  double movingProgress = 0;
  bool fadingOut = false;
public:
  vtkSmartPointer<vtkActor> getActor() override;

  void setVisible(bool visible) override;

  void updateData(int t) override;

  explicit StaticBadge(const std::string &datapath, double size);

  void reset() override;

  void setZ(double z);
};

#endif //STATICBADGE_H
