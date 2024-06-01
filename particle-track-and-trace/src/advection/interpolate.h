#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <vector>

#include "UVGrid.h"

/**
 * Bilinearly interpolate the point (time, lat, lon) to produce the interpolated velocity.
 * Since it is in 3D, this means that it interpolates against 8 points (excluding edges).
 * As described in https://numerical.recipes/book.html Chapter 3.6
 * @param uvGrid velocity grid
 * @param time time of point
 * @param lat latitude of point
 * @param lon longitude of point
 * @return interpolated velocity
 */
Vel bilinearinterpolate(const UVGrid &uvGrid, int time, double lat, double lon);

/**
 * Helper function for bilnearly interpolating a vector of points
 * @param uvGrid velocity grid
 * @param points vector of points
 * @return interpolated velocities
 */
std::vector<Vel> bilinearinterpolation(const UVGrid &uvGrid, std::vector<std::tuple<int, double, double>> points);

bool isNearestNeighbourZero(const UVGrid &uvGrid, int time, double lat, double lon);

#endif //INTERPOLATE_H
