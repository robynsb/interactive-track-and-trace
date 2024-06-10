#ifndef FILEBADGEFACTORY_H
#define FILEBADGEFACTORY_H

#include "../statistics/Statistic.h"
#include "Achievement.h"
#include "Badge.h"
#include "../statistics/BadgesAcquired.h"

#include <map>
#include <memory>

/**
 * Creates badges and corresponding SimpleAchievements by reading them from the data path.
 */
class FileBadgeFactory {
public:
  /**
   * Register a statistic and its name.
   * @param name of statistic
   * @param statistic to be used for SimpleAchievement.
   */
  void addStatistic(std::string name, const std::shared_ptr<Statistic>& statistic);

  /**
   * Looks into the datapath for a directory named badges.
   * Inside badges expects to find more directories with the same names as statistics that were
   * previously added.
   * Inside each statistic directory expects to find png files of badges and expects that each png file
   * has the name of number.
   * Creates for each such file a SimpleAchievement whose requiredValue is of the number in the file name.
   * And the png file is used to construct a SimpleBadge.
   *
   * For example:
   * Given the following direcectory structure
   * badges/
   *    days/
   *        91.25.png
   *        182.png
   *    food/
   *        6000.png
   * The factory creates 3 StaticBadges and 3 SimpleAchievements,
   * 2 of them will be achieved when 91.25 days have passed and when 182 days have passed respectively.
   * The last one will be achieved when the food statistic is greater than 6000.
   */
  std::vector<std::pair<std::shared_ptr<Achievement>, std::shared_ptr<Badge>>> getBadges() const;

  /**
   * Constructor.
   * @param datapath path to the badges directory.
   * @param badgesAcquired needed for the badgesAcquired statistic. All the created achievements are TrackedAchievements
   * and need to know where to broadcast their status.
   */
  explicit FileBadgeFactory(const std::string &datapath, const std::shared_ptr<BadgesAcquired>& badgesAcquired);
private:

  static constexpr double badgeSize = 0.3;

  std::vector<std::pair<std::shared_ptr<Achievement>, std::shared_ptr<Badge>>> getBadges(std::string badgesDirectory, std::string statisticName) const;
  std::unique_ptr<Achievement> createAchievement(std::string statistic, double requiredValue) const;
  std::unique_ptr<Badge> createBadge(std::string assetPath, std::string assetName) const;

  std::map<std::string, std::shared_ptr<Statistic>> statistics;
  std::shared_ptr<BadgesAcquired> badgesAcquired;
  const std::string datapath;

};


#endif //FILEBADGEFACTORY_H
