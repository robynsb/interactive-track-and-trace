#ifndef SNAPBOUNDARYCONDITIONKERNEL_H
#define SNAPBOUNDARYCONDITIONKERNEL_H

#include <memory>
#include "AdvectionKernel.h"
#include "../UVGrid.h"

/**
 * When a point goes outside of the grid, this Kernel will snap it to the closest edge.
 * This kernel wraps around another kernel, and implements only the boundary conditions.
 */
class SnapBoundaryConditionKernel: public AdvectionKernel {
  std::unique_ptr<AdvectionKernel> kernel;
  std::shared_ptr<UVGrid> uvGrid;
public:
  /**
   * Construct the kernel.
   * @param kernel The kernel to be called first before boundary conditions are applied
   * @param uvGrid The grid that is used to check boundary conditions against
   */
  SnapBoundaryConditionKernel(std::unique_ptr<AdvectionKernel> kernel, std::shared_ptr<UVGrid> uvGrid);

  std::pair<double, double> advect(int time, double latitude, double longitude, int dt) const override;
};


#endif //SNAPBOUNDARYCONDITIONKERNEL_H
