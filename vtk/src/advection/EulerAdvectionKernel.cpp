
#include "EulerAdvectionKernel.h"
#include "interpolate.h"

using namespace std;

EulerAdvectionKernel::EulerAdvectionKernel(std::shared_ptr<UVGrid> grid, int dt) : grid(grid), dt(dt) {}

std::pair<double, double> EulerAdvectionKernel::advect(int time, double latitude, double longitude) const {
  auto [u, v] = bilinearinterpolate(*grid, time, latitude, longitude);

  return {latitude + metreToDegrees(v * dt), longitude + metreToDegrees(u * dt)};
}
