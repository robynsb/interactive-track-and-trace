#ifndef SNAPBOUNDARYCONDITIONKERNEL_H
#define SNAPBOUNDARYCONDITIONKERNEL_H

#include <memory>
#include "AdvectionKernel.h"
#include "../UVGrid.h"

/**
 * When
 */
class SnapBoundaryConditionKernel: public AdvectionKernel {
  std::unique_ptr<AdvectionKernel> kernel;
  std::shared_ptr<UVGrid> uvGrid;
public:
  SnapBoundaryConditionKernel(std::unique_ptr<AdvectionKernel> kernel, std::shared_ptr<UVGrid> uvGrid);

private:
  std::pair<double, double> advect(int time, double latitude, double longitude, int dt) const override;
};


#endif //SNAPBOUNDARYCONDITIONKERNEL_H
