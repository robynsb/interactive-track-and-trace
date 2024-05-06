#ifndef ADVECTION_RK4ADVECTIONKERNEL_H
#define ADVECTION_RK4ADVECTIONKERNEL_H

#include "AdvectionKernel.h"
#include "UVGrid.h"

/**
 * Implementation of Advection kernel using RK4 integration
 * See https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods for more details.
 * Uses bilinear interpolation as implemented in interpolate.h
 */
class RK4AdvectionKernel: public AdvectionKernel {
private:
    std::shared_ptr<UVGrid> grid;
    int dt;
public:
    explicit RK4AdvectionKernel(std::shared_ptr<UVGrid> grid, int dt);
    std::pair<double, double> advect(int time, double latitude, double longitude) const override;

};


#endif //ADVECTION_RK4ADVECTIONKERNEL_H
