#ifndef ADVECTION_ADVECTIONKERNEL_H
#define ADVECTION_ADVECTIONKERNEL_H

#include <tuple>

#include "Vel.h"


/*
 * Implement this class for every integration method.
 */
class AdvectionKernel {
public:
    /**
     * This function must take a time, latitude and longitude of a particle and must output
     * a new latitude and longitude after being advected once for AdvectionKernel::DT time as defined above.
     * @param time Time since the beginning of the data
     * @param latitude Latitude of particle
     * @param longitude Longitude of particle
     * @return A pair of latitude and longitude of particle.
     */
    virtual std::pair<double, double> advect(int time, double latitude, double longitude, int dt) const = 0;

    // Taken from Parcels https://github.com/OceanParcels/parcels/blob/daa4b062ed8ae0b2be3d87367d6b45599d6f95db/parcels/tools/converters.py#L155
    const static double metreToDegrees(double metre) {
        return metre / 1000. / 1.852 / 60.;
    }

    virtual ~AdvectionKernel() = default; // Apparently I need this, idk why
};

#endif //ADVECTION_ADVECTIONKERNEL_H
