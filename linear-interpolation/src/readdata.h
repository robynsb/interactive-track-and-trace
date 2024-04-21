#ifndef LINEARINTERPOLATE_READDATA_H
#define LINEARINTERPOLATE_READDATA_H

#include "vecutils.h"

/**
 * reads the file hydrodynamic_U.h5
 * @return a pair of the data vector of the contents and its dimensions to be used with mdspan
 */
std::pair<std::vector<double>, std::dextents<std::size_t, 3>> readHydrodynamicU();

/**
 * reads the file hydrodynamic_V.h5
 * @return a pair of the data vector of the contents and its dimensions to be used with mdspan
 */
std::pair<std::vector<double>, std::dextents<std::size_t, 3>> readHydrodynamicV();

/**
 * Reads the file grid.h5
 * @return a tuple of (times, latitude, longitude)
 */
std::tuple<std::vector<int>, std::vector<double>, std::vector<double>> readGrid();

#endif //LINEARINTERPOLATE_READDATA_H
