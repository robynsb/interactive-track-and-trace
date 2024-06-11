#ifndef QUADRATICBEZIERROUTE_H
#define QUADRATICBEZIERROUTE_H

#include "VesselRoute.h"

/**
 * QuadraticBezierRoute uses 3 control points to create a bezier curve for a vessel route.
 */
class QuadraticBezierRoute : public VesselRoute {
public:
  std::pair<double, double> getPosition(int time) override;

  bool isWrecking(int time) override;

  /**
   * Constructor.
   * @param startTime time when the vessel starts moving
   * @param duration how long it takes for the vessel to move from (lon1, lat1) to (lon3, lat3).
   * @param depositionPeriod every depositionPeriod seconds the ship will wreck.
   * @param lon1 longitude of first control point
   * @param lat1 latitude of first control point
   * @param lon2 longitude of second control point
   * @param lat2 latitude of second control point
   * @param lon3 longitude of third control point
   * @param lat3 latitude of third control point
   */
  QuadraticBezierRoute(int startTime, int duration, int depositionPeriod, int lon1, int lat1,
                       int lon2, int lat2, int lon3, int lat3);
private:
  const int duration;
  const int startTime;
  double lon1;
  double lat1;
  double lon2;
  double lat2;
  double lon3;
  double lat3;
  int depositionPeriod;
  int currentPeriodNumber = 0;

};


#endif //QUADRATICBEZIERROUTE_H
