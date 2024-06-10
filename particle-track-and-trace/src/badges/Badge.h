#ifndef BADGE_H
#define BADGE_H

#include <vtkActor.h>

/**
 * A Badge is a vtkActor that is displayed when an Achievement is achieved.
 * Used in the Badges layer.
 */
class Badge {
public:
  /**
   * Displays the badge.
   */
  void collect();

  /**
   * Reset the badge. Called when the game ends.
   */
  virtual void reset();

  /**
   * Get the vtkActor of the badge.
   */
  virtual vtkSmartPointer<vtkActor> getActor() = 0;

  /**
   * Set visibility of actor.
   */
  virtual void setVisible(bool visible) = 0;

  /**
   * Called every timestep that the badge is collected.
   * Can be used for animating the badges.
   */
  virtual void updateData(int t);

  bool isCollected();

  virtual ~Badge() = default;
private:
  bool collected = false;

};

#endif //BADGE_H
