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

  virtual ~VesselRoute() = default;

  const static double quadraticBezier1D(double p0, double p1, double p2, double t) {
    return (1-t)*(1-t)*p0 + 2*(1-t)*t*p1 + t*t*p2;
  }
};

#endif //VESSELROUTE_H
