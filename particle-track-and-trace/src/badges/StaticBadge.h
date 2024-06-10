#ifndef STATICBADGE_H
#define STATICBADGE_H

#include "Badge.h"
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <SFML/Audio.hpp>

/**
 * StaticBadge is a badge represented by a simple image asset png.
 */
class StaticBadge : public Badge {
public:
  /**
   * Set visibility of badge.
   */
  void setVisible(bool visible) override;

  /**
   * Creates badge actor.
   * @param datapath to find the image file.
   * @param name of the image file.
   * @param size of that the badge should have.
   */
  explicit StaticBadge(const std::string &datapath, std::string name, double size);

  /**
   * updateData used for animating the badge from the top of the screen and fading it out afterwards.
   */
  void updateData(int t) override;

  /**
   * Resets the badge so that it can be collected again.
   */
  void reset() override;

  vtkSmartPointer<vtkActor> getActor() override;
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
