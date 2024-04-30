#include "RK4AdvectionKernel.h"
#include "interpolate.h"

using namespace std;

RK4AdvectionKernel::RK4AdvectionKernel(std::shared_ptr<UVGrid> grid): grid(grid) { }

std::pair<double, double> RK4AdvectionKernel::advect(int time, double latitude, double longitude) const {
    auto [u1, v1] = bilinearinterpolation(*grid, time, latitude, longitude);
//    lon1, lat1 = (particle.lon + u1*.5*particle.dt, particle.lat + v1*.5*particle.dt);
    double lon1 = longitude + metreToDegrees(v1 * 0.5*DT);
    double lat1 = latitude + metreToDegrees(u1 * 0.5*DT);

//    (u2, v2) = fieldset.UV[time + .5 * particle.dt, particle.depth, lat1, lon1, particle]
    auto [u2, v2] = bilinearinterpolation(*grid, time + 0.5*DT, lat1, lon1);

//    lon2, lat2 = (particle.lon + u2*.5*particle.dt, particle.lat + v2*.5*particle.dt)
    double lon2 = longitude + metreToDegrees(v2 * 0.5 * DT);
    double lat2 = latitude + metreToDegrees(u2 * 0.5 * DT);

//    (u3, v3) = fieldset.UV[time + .5 * particle.dt, particle.depth, lat2, lon2, particle]
    auto [u3, v3] = bilinearinterpolation(*grid, time + 0.5 * DT, lat2, lon2);

//    lon3, lat3 = (particle.lon + u3*particle.dt, particle.lat + v3*particle.dt)
    double lon3 = longitude + metreToDegrees(v3 * DT);
    double lat3 = latitude + metreToDegrees(u3 * DT);

//    (u4, v4) = fieldset.UV[time + particle.dt, particle.depth, lat3, lon3, particle]
    auto [u4, v4] = bilinearinterpolation(*grid, time + DT, lat3, lon3);

    double lonFinal = longitude + metreToDegrees((v1 + 2 * v2 + 2 * v3 + v4) / 6.0 * DT);
    double latFinal = latitude + metreToDegrees((u1 + 2 * u2 + 2 * u3 + u4) / 6.0 * DT);

    return {latFinal, lonFinal};
}
