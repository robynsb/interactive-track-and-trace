#ifndef ADVECTION_EULERADVECTIONKERNEL_H
#define ADVECTION_EULERADVECTIONKERNEL_H

#include "AdvectionKernel.h"
#include "UVGrid.h"

class EulerAdvectionKernel: public AdvectionKernel {
private:
    std::shared_ptr<UVGrid> grid;
public:
    explicit EulerAdvectionKernel(std::shared_ptr<UVGrid> grid);
    std::pair<double, double> advect(int time, double latitude, double longitude) const override;

};


#endif //ADVECTION_EULERADVECTIONKERNEL_H
