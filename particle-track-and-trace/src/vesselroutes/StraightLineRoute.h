#ifndef STRAIGHTLINEROUTE_H
#define STRAIGHTLINEROUTE_H

#include <vector>
#include "VesselRoute.h"

class StraightLineRoute : public VesselRoute {
private:
  std::vector<std::tuple<int, double, double>> durationlonlats;
  int stage = 0;
  int travelTimeInStage = 0;
  int lastTime = 0;
  bool inNewStage = false;
public:
  StraightLineRoute();

  void addKeyPoint(int duration, double lon, double lat);

  std::pair<double, double> getPosition(int time) override;

  bool isWrecking(int time) override;
};

#endif //STRAIGHTLINEROUTE_H
