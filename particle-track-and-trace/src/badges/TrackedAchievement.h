#ifndef TRACKEDACHIEVEMENT_H
#define TRACKEDACHIEVEMENT_H

#include "Achievement.h"
#include "../statistics/BadgesAcquired.h"

#include <memory>

/**
 * Wraps around another achievement and broadcasts its achieved state to BadgesAcquired statistic.
 */
class TrackedAchievement : public Achievement {
public:
  /**
   * Constructor.
   * @param achievement to wrap around.
   * @param badgeStatusSetter callback to broadcast state.
   */
  TrackedAchievement(std::unique_ptr<Achievement> achievement,
                     const std::function<void(bool)> &badgeStatusSetter);

  /**
   * Passes through the achieved state of achievement and broadcasts the state using badgeStatusSetter.
   */
  bool isAchieved() override;

private:
  std::unique_ptr<Achievement> achievement;
  std::function<void (bool)> badgeStatusSetter;
};


#endif //TRACKEDACHIEVEMENT_H
