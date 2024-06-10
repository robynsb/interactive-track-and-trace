#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

/**
 * An Achievement logically decides when the player has achieved a particular goal.
 * This will typically be done by checking against one or more Statistic(s).
 */
class Achievement {
public:
  /**
   * Returns true if the achievement is achieved.
   * Returns false otherwise.
   */
  virtual bool isAchieved() = 0;

  virtual ~Achievement() = default;
};

#endif //ACHIEVEMENT_H
