#ifndef STATICBADGE_H
#define STATICBADGE_H

#include "Badge.h"
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <SFML/Audio.hpp>

class StaticBadge : public Badge {
public:
  vtkSmartPointer<vtkActor> getActor() override;

  void setVisible(bool visible) override;

  void updateData(int t) override;

  explicit StaticBadge(const std::string &datapath, std::string name, double size);

  void reset() override;

  void setZ(double z);
private:
  static constexpr double initY {1.5};
  static constexpr double targetY {0.85};
  static constexpr double fadeOutIn {5};
  vtkNew<vtkPoints> position;
  vtkNew<vtkActor> texturedPlane;
  bool moving = false;
  double movingProgress {0};
  bool fadingOut = false;

  sf::SoundBuffer buffer;
  sf::Sound sound;
};

#endif //STATICBADGE_H
