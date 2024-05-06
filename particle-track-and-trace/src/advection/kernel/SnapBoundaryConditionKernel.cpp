#include "SnapBoundaryConditionKernel.h"

SnapBoundaryConditionKernel::SnapBoundaryConditionKernel(std::unique_ptr<AdvectionKernel> kernel,
                                                         std::shared_ptr<UVGrid> uvGrid) :
                                                         kernel(std::move(kernel)),
                                                         uvGrid(uvGrid) { }
std::pair<double, double> SnapBoundaryConditionKernel::advect(int time, double latitude, double longitude, int dt) const {
  auto [newLat, newLon] = kernel->advect(time, latitude, longitude, dt);
  double minLat = uvGrid->lats.front();
  double maxLat = uvGrid->lats.back();
  double minLon = uvGrid->lons.front();
  double maxLon = uvGrid->lons.back();
  if (newLat < minLat) {
    newLat = minLat;
  }
  if (newLat > maxLat) {
    newLat = maxLat;
  }
  if (newLon < minLon) {
    newLon = minLon;
  }
  if (newLon > maxLon) {
    newLon = maxLon;
  }
  return {newLat, newLon};
}