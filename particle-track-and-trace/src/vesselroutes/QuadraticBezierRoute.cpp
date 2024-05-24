#include "QuadraticBezierRoute.h"

using namespace std;

const double quadraticBezier1D(double p0, double p1, double p2, double t) {
  return (1-t)*(1-t)*p0 + 2*(1-t)*t*p1 + t*t*p2;
}

std::pair<double, double> QuadraticBezierRoute::getPosition(int time) const {
  if (time < startTime) {
    return {lon1, lat1};
  }
  double t = static_cast<double>((time - startTime) % duration) / duration;

  return {
          quadraticBezier1D(lon1, lon2, lon3, t),
          quadraticBezier1D(lat1, lat2, lat3, t)
  };
}


QuadraticBezierRoute::QuadraticBezierRoute(int startTime, int duration, int depositionPeriod, int lon1, int lat1,
                                           int lon2, int lat2, int lon3, int lat3) :
        duration(duration), startTime(startTime), lat1(lat1), lon1(lon1),
        lat2(lat2), lon2(lon2), lon3(lon3), lat3(lat3), depositionPeriod(depositionPeriod) {}

bool QuadraticBezierRoute::isWrecking(int time) {
  bool isWrecked = time / depositionPeriod != currentPeriodNumber;
  currentPeriodNumber = time / depositionPeriod;
  return isWrecked;
}
