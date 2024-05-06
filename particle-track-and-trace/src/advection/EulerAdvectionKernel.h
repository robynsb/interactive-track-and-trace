#ifndef EULERADVECTIONKERNEL_H
#define EULERADVECTIONKERNEL_H

#include "AdvectionKernel.h"
#include "UVGrid.h"

/**
 * Implementation of AdvectionKernel.
 * The basic equation is:
 * new_latitude = latitude + v*DT
 * new_longitude = longitude + u*DT
 *
 * Uses bilinear interpolation as implemented in interpolate.h
 */
class EulerAdvectionKernel: public AdvectionKernel {
private:
    std::shared_ptr<UVGrid> grid;
public:
    explicit EulerAdvectionKernel(std::shared_ptr<UVGrid> grid);
    std::pair<double, double> advect(int time, double latitude, double longitude, int dt) const override;

};


#endif //EULERADVECTIONKERNEL_H
