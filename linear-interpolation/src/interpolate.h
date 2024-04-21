#ifndef LINEARINTERPOLATE_INTERPOLATE_H
#define LINEARINTERPOLATE_INTERPOLATE_H

#include <vector>

#include "UVGrid.h"

point bilinearInterpolate(const UVGrid &uvGrid, std::tuple<int, double, double> timeLatLong);

std::vector<double> bilinearInterpolate();

#endif //LINEARINTERPOLATE_INTERPOLATE_H
