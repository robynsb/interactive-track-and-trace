
#include "EulerAdvectionKernel.h"
#include "interpolate.h"

using namespace std;

EulerAdvectionKernel::EulerAdvectionKernel(std::shared_ptr<UVGrid> grid): grid(grid) { }

std::pair<double, double> EulerAdvectionKernel::advect(int time, double latitude, double longitude) const {
    auto [u, v] = bilinearinterpolate(*grid, time, latitude, longitude);

    return {latitude+metreToDegrees(v*DT), longitude+metreToDegrees(u*DT)};
}
