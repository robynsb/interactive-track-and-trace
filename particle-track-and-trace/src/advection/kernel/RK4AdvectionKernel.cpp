#include "RK4AdvectionKernel.h"
#include "../interpolate.h"

using namespace std;

RK4AdvectionKernel::RK4AdvectionKernel(std::shared_ptr<UVGrid> grid): grid(grid) { }

std::pair<double, double> RK4AdvectionKernel::advect(int time, double latitude, double longitude, int dt) const {
    auto [u1, v1] = bilinearinterpolate(*grid, time, latitude, longitude);
//    lon1, lat1 = (particle.lon + u1*.5*particle.dt, particle.lat + v1*.5*particle.dt);
    double lon1 = longitude + metreToDegrees(u1 * 0.5*dt);
    double lat1 = latitude + metreToDegrees(v1 * 0.5*dt);

//    (u2, v2) = fieldset.UV[time + .5 * particle.dt, particle.depth, lat1, lon1, particle]
    auto [u2, v2] = bilinearinterpolate(*grid, time + 0.5 * dt, lat1, lon1);

//    lon2, lat2 = (particle.lon + u2*.5*particle.dt, particle.lat + v2*.5*particle.dt)
    double lon2 = longitude + metreToDegrees(u2 * 0.5 * dt);
    double lat2 = latitude + metreToDegrees(v2 * 0.5 * dt);

//    (u3, v3) = fieldset.UV[time + .5 * particle.dt, particle.depth, lat2, lon2, particle]
    auto [u3, v3] = bilinearinterpolate(*grid, time + 0.5 * dt, lat2, lon2);

//    lon3, lat3 = (particle.lon + u3*particle.dt, particle.lat + v3*particle.dt)
    double lon3 = longitude + metreToDegrees(u3 * dt);
    double lat3 = latitude + metreToDegrees(v3 * dt);

//    (u4, v4) = fieldset.UV[time + particle.dt, particle.depth, lat3, lon3, particle]
    auto [u4, v4] = bilinearinterpolate(*grid, time + dt, lat3, lon3);

    double lonFinal = longitude + metreToDegrees((u1 + 2 * u2 + 2 * u3 + u4) / 6.0 * dt);
    double latFinal = latitude + metreToDegrees((v1 + 2 * v2 + 2 * v3 + v4) / 6.0 * dt);

    return {latFinal, lonFinal};
}
