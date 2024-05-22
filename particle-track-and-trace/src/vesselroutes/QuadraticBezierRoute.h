#ifndef QUADRATICBEZIERROUTE_H
#define QUADRATICBEZIERROUTE_H

#include "VesselRoute.h"

class QuadraticBezierRoute : public VesselRoute {
  const int duration;
  const int startTime;
  double lon1;
  double lat1;
  double lon2;
  double lat2;
  double lon3;
  double lat3;

public:
  std::pair<double, double> getPosition(int time) const override;

  QuadraticBezierRoute(int startTime, int duration, int lon1, int lat1,
                       int lon2, int lat2, int lon3, int lat3);
};


#endif //QUADRATICBEZIERROUTE_H
