#ifndef ADVECTION_ADVECTIONKERNEL_H
#define ADVECTION_ADVECTIONKERNEL_H

#include <tuple>

#include "Vel.h"

#define DT 50

/*
 * Implement this class for every integration method.
 */
class AdvectionKernel {
public:
    /**
     * This function must take a time, latitude and longitude of a particle and must output
     * a new latitude and longitude after being advected once for DT time as defined above.
     * @param time Time since the beginning of the data
     * @param latitude Latitude of particle
     * @param longitude Longitude of particle
     * @return A pair of latitude and longitude of particle.
     */
    virtual std::pair<double, double> advect(int time, double latitude, double longitude) const = 0;
};

#endif //ADVECTION_ADVECTIONKERNEL_H
