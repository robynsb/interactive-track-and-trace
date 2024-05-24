#include <cassert>
#include <iostream>
#include "StraightLineRoute.h"

using namespace std;

void StraightLineRoute::addKeyPoint(int duration, double lon, double lat) {
  durationlonlats.push_back({duration, lon, lat});
}

std::pair<double, double> StraightLineRoute::getPosition(int time) {
  int dt = time - lastTime;
  if (dt < 0) {
    dt = time;
  }
  lastTime = time;
  auto [duration, lon, lat] = durationlonlats.at(stage);
  int timeRemainingInStage = duration - travelTimeInStage;
  if (timeRemainingInStage > dt) {
    travelTimeInStage += dt;
  } else {
    assert(get<0>(durationlonlats.at(stage)) > dt);
    inNewStage = true;
    stage = (stage + 1) % durationlonlats.size();
    travelTimeInStage = dt - timeRemainingInStage;
  }

  auto [dur, lon1, lat1] = durationlonlats.at(stage);

  if (stage == durationlonlats.size()-1) {
    stage = 0;
    travelTimeInStage = 0;
    return {lon1, lat1};
  }
  auto [_, lon2, lat2] = durationlonlats.at(stage+1);
  double t = static_cast<double>(travelTimeInStage) / dur;

  return {lerp(lon1, lon2, t), lerp(lat1, lat2, t)};
}

bool StraightLineRoute::isWrecking(int time) {
  if (inNewStage) {
    inNewStage = !inNewStage;
    return true;
  }
  return false;
}

StraightLineRoute::StraightLineRoute() {}

