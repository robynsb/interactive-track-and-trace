#ifndef VESSELROUTE_H
#define VESSELROUTE_H

#include <utility>

/**
 * Specifies a route that vessel should travel through time.
 */
class VesselRoute {
public:
  /**
   * Update function will produce the location at some point in time.
   * @param time time in seconds
   * @return position pair in (longitude, latitude) degrees.
   */
  virtual std::pair<double, double> getPosition(int time) const = 0;

  virtual bool isWrecking(int time) = 0;

  virtual ~VesselRoute() = default;

};

#endif //VESSELROUTE_H
