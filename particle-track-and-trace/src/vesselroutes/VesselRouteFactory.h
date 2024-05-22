#ifndef VESSELROUTEFACTORY_H
#define VESSELROUTEFACTORY_H

#include "../advection/UVGrid.h"
#include "../layers/VesselLayer.h"

std::shared_ptr<VesselLayer> createVesselLayer(std::shared_ptr<UVGrid> uvGrid, std::string datapath);

#endif //VESSELROUTEFACTORY_H
