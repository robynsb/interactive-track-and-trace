#ifndef VESSELS_H
#define VESSELS_H


#include <vtkPoints.h>
#include <vtkPolyData.h>
#include "Layer.h"
#include "../vesselroutes/VesselRoute.h"
#include "../advection/UVGrid.h"

class Vessels : public Layer {
private:
  vtkSmartPointer<vtkPoints> deposition;
  vtkSmartPointer<vtkPoints> position;
  vtkSmartPointer<vtkIntArray> particlesBeached;
  vtkSmartPointer<vtkPolyData> data;
  std::vector<std::shared_ptr<VesselRoute>> routes;
  std::shared_ptr<UVGrid> uvGrid;
public:
  void addRoute(std::shared_ptr<VesselRoute> route);
  Vessels(std::shared_ptr<UVGrid> uvGrid, std::string path);
  void setDepositAndBeached(vtkSmartPointer<vtkPoints> deposit, vtkSmartPointer<vtkIntArray> particlesBeached);

  void updateData(int t) override;
};

#endif //VESSELS_H