#ifndef ADVECTION_RK4ADVECTIONKERNEL_H
#define ADVECTION_RK4ADVECTIONKERNEL_H


#include "AdvectionKernel.h"
#include "UVGrid.h"

class RK4AdvectionKernel: public AdvectionKernel {
private:
    std::shared_ptr<UVGrid> grid;
public:
    explicit RK4AdvectionKernel(std::shared_ptr<UVGrid> grid);
    std::pair<double, double> advect(int time, double latitude, double longitude) const override;

};


#endif //ADVECTION_RK4ADVECTIONKERNEL_H
