#ifndef ADVECTION_ADVECTIONKERNEL_H
#define ADVECTION_ADVECTIONKERNEL_H

#include <tuple>

#include "Vel.h"

#define DT 50

class AdvectionKernel {
public:
    virtual std::pair<double, double> advect(int time, double latitude, double longitude) const = 0;
};

#endif //ADVECTION_ADVECTIONKERNEL_H
