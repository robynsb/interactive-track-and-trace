#ifndef VESSELLAYER_H
#define VESSELLAYER_H


#include <vtkPoints.h>
#include <vtkPolyData.h>
#include "Layer.h"
#include "../vesselroutes/VesselRoute.h"
#include "../advection/UVGrid.h"

class VesselLayer : public Layer {
private:
  vtkSmartPointer<vtkPoints> position;
  vtkSmartPointer<vtkPolyData> data;
  std::vector<std::shared_ptr<VesselRoute>> routes;
  std::shared_ptr<UVGrid> uvGrid;
public:
  void addRoute(std::shared_ptr<VesselRoute> route);
  VesselLayer(std::shared_ptr<UVGrid> uvGrid, std::string path);

  void updateData(int t) override;
};

#endif //VESSELLAYER_H