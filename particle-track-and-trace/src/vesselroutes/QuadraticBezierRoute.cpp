#include "QuadraticBezierRoute.h"

using namespace std;


std::pair<double, double> QuadraticBezierRoute::getPosition(int time) const {
//  // Southend-on-sea
//  double lon1 = 0.6833443334080538;
//  double lat1 = 51.513525377373554;
//  // Somewhere in the ocean
//  double lon2 = 4.278963276069124;
//  double lat2 = 53.595354574287875;
//  // Amsterdam
//  double lon3 = 4.905113199673045;
//  double lat3 = 52.37897444844786;
  if (time < startTime) {
    return {lon1, lat1};
  }
  double t = static_cast<double>((time - startTime) % duration) / duration;

  return {
          quadraticBezier1D(lon1, lon2, lon3, t),
          quadraticBezier1D(lat1, lat2, lat3, t)
  };
}

QuadraticBezierRoute::QuadraticBezierRoute(int startTime, int duration, int lon1, int lat1,
                                           int lon2, int lat2, int lon3, int lat3) :
        duration(duration), startTime(startTime), lat1(lat1), lon1(lon1),
        lat2(lat2), lon2(lon2), lon3(lon3), lat3(lat3) {}
