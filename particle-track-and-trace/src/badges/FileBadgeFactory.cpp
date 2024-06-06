#include "FileBadgeFactory.h"

#include "SimpleAchievement.h"
#include "StaticBadge.h"
#include "TrackedAchievement.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

void FileBadgeFactory::addStatistic(std::string name, const std::shared_ptr<Statistic> &statistic) {
  statistics[name] = statistic;
}

std::string trimExtension(const std::string &filename) {
  size_t lastDotIndex = filename.find_last_of(".");
  if (lastDotIndex != std::string::npos) {
    return filename.substr(0, lastDotIndex);
  }
  return filename; // No extension found
}

std::string removeQuotes(const std::string &str) {
  std::string result = str;
  size_t pos = result.find_first_of("\"");
  while (pos != std::string::npos) {
    result.erase(pos, 1);
    pos = result.find_first_of("\"", pos);
  }
  return result;
}

vector<string> findBadgesInDir(const string &path) {
  vector<string> names;
  try {
    if (fs::exists(path) && fs::is_directory(path)) {
      for (const auto &entry: fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".png") {
          string filename = entry.path().filename();
          string noQuotesFilename = removeQuotes(filename);
          names.push_back(noQuotesFilename);
        }
      }
    } else {
      std::cerr << "Path does not exist or is not a directory." << std::endl;
    }
  } catch (const fs::filesystem_error &e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return names;
}

vector<string> getDirectoryNames(string path) {
  vector<string> names;
  try {
    if (fs::exists(path) && fs::is_directory(path)) {
      for (const auto &entry: fs::directory_iterator(path)) {
        if (entry.is_directory()) {
          names.push_back(entry.path().filename());
        }
      }
    } else {
      std::cerr << "Path does not exist or is not a directory." << std::endl;
    }
  } catch (const fs::filesystem_error &e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return names;
}

unique_ptr<Badge> FileBadgeFactory::createBadge(string assetPath, string assetName) const {
  return make_unique<StaticBadge>(assetPath, assetName, badgeSize);
}

vector<pair<shared_ptr<Achievement>, shared_ptr<Badge>>> FileBadgeFactory::getBadges(
        string assetPath,
        string statisticName) const {
  vector<pair<shared_ptr<Achievement>, shared_ptr<Badge>>> badges;
  vector<string> badgeNames = findBadgesInDir(assetPath + "/badges/" + statisticName);
  for (string badgeName: badgeNames) {
    string badgeNameNoExtension = trimExtension(badgeName);
    auto achievement = createAchievement(statisticName, stod(badgeNameNoExtension));
    auto badge = createBadge(assetPath, "/badges/" + statisticName + "/" + badgeName);
    badges.emplace_back(std::move(achievement), std::move(badge));
  }

  return badges;
}

vector<pair<shared_ptr<Achievement>, shared_ptr<Badge>>> FileBadgeFactory::getBadges() const {
  vector<pair<shared_ptr<Achievement>, shared_ptr<Badge>>> badges;
  string badgesDirectory = datapath + "/badges";
  vector<string> statisticNames = getDirectoryNames(badgesDirectory);
  for (const string &statisticName: statisticNames) {
    auto achievementBadges = getBadges(datapath, statisticName);
    badges.insert(badges.end(), achievementBadges.begin(), achievementBadges.end());
  }
  return badges;
}

FileBadgeFactory::FileBadgeFactory(const std::string &datapath, const std::shared_ptr<BadgesAcquired> &badgesAcquired)
        : datapath(datapath),
          badgesAcquired(badgesAcquired) {}

std::unique_ptr<Achievement> FileBadgeFactory::createAchievement(
        std::string statisticName, double requiredValue
) const {
  shared_ptr<Statistic> statistic = statistics.at(statisticName);
  auto achiement = make_unique<SimpleAchievement>(statistic, requiredValue);
  return make_unique<TrackedAchievement>(std::move(achiement), badgesAcquired->getBadgeStatusSetter());
}
