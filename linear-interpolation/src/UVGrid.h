#ifndef LINEARINTERPOLATE_UVGRID_H
#define LINEARINTERPOLATE_UVGRID_H

#include <vector>
#include "vecutils.h"
#include "point.h"

class UVGrid {
private:
    /**
     * u == Eastward Current Velocity in the Water Column
     * v == Northward Current Velocity in the Water Column
     */
    std::vector<point> uvData;
public:
    UVGrid();

    // The step functions assume regular spacing
    double lonStep() const;
    double latStep() const;
    int timeStep() const;

    std::vector<int> times;
    std::vector<double> lats;
    std::vector<double> lons;

    arr3d<point> uvMatrix;
};

#endif //LINEARINTERPOLATE_UVGRID_H
