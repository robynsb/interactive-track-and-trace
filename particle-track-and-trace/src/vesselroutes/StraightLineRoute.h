#ifndef STRAIGHTLINEROUTE_H
#define STRAIGHTLINEROUTE_H

#include <vector>
#include "VesselRoute.h"

/**
 * StraightLineRoute allows adding keypoints which are points in (duration, lon, lat) space. This vessel route will then
 * move in straight lines from one key point to the next.
 * Note that the meaning of duration:
 * It will take dur1 seconds (in simulation time) for the vessel to move from (dur1, lon1, lat1)
 * to (dur2, lon2, lat2).
 *
 * After reaching the last point (durN, lonN, latN) it will stay there for durN seconds and then start again
 * at the initial keypoint.
 */
class StraightLineRoute : public VesselRoute {
public:
  /**
   * Constructor.
   */
  StraightLineRoute();

  /**
   * Add a keypoint.
   * @param duration in seconds
   * @param lon longitude in degrees
   * @param lat latitude in degrees
   */
  void addKeyPoint(int duration, double lon, double lat);

  std::pair<double, double> getPosition(int time) override;

  bool isWrecking(int time) override;
private:
  std::vector<std::tuple<int, double, double>> durationlonlats;
  int stage = 0;
  int travelTimeInStage = 0;
  int lastTime = 0;
  bool inNewStage = false;
};

#endif //STRAIGHTLINEROUTE_H
