#ifndef VESSELROUTEFACTORY_H
#define VESSELROUTEFACTORY_H

#include "../advection/UVGrid.h"
#include "../layers/Vessels.h"

/**
 * Creates a Vessel layer.
 * Uses some hard coded values to create an interesting set of vessel routes.
 */
std::shared_ptr<Vessels> createVesselLayer(std::shared_ptr<UVGrid> uvGrid, std::string datapath);

#endif //VESSELROUTEFACTORY_H
