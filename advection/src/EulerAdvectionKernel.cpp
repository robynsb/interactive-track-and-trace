
#include "EulerAdvectionKernel.h"

using namespace std;

EulerAdvectionKernel::EulerAdvectionKernel(std::shared_ptr<UVGrid> grid) { }

std::pair<double, double> EulerAdvectionKernel::advect(int time, double latitude, double longitude) const {
    auto [u,v] = (*grid)[time, latitude, longitude];
    return {latitude+u*DT, longitude+v*DT};
}
