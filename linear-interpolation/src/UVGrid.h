#ifndef LINEARINTERPOLATE_UVGRID_H
#define LINEARINTERPOLATE_UVGRID_H

#include <vector>
#include "Vel.h"

class UVGrid {
private:
    /**
     * 1D data vector of all the us and vs
     */
    std::vector<Vel> uvData;
public:
    UVGrid();

    size_t timeSize;
    size_t latSize;
    size_t lonSize;

    /**
     * Assuming grid is a regular grid, gives the longitudinal spacing of grid.
     * @return longitudinal spacing
     */
    double lonStep() const;

    /**
     * Assuming grid is a regular grid, gives the latitudinal spacing of grid.
     * @return latitudinal spacing
     */
    double latStep() const;

    /**
     * Assuming grid is a regular grid, gives the time spacing of grid.
     * @return time spacing
     */
    int timeStep() const;

    std::vector<int> times;
    std::vector<double> lats;
    std::vector<double> lons;

    /**
     * The 3D index into the data
     * @return Velocity at that index
     */
    const Vel& operator[](size_t timeIndex, size_t latIndex, size_t lonIndex) const;

    // Friend declaration for the stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const UVGrid& vel);

    void printSlice(size_t t);
};


#endif //LINEARINTERPOLATE_UVGRID_H
