#ifndef UVGRID_H
#define UVGRID_H

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

    /**
     * The matrix has shape (timeSize, latSize, lonSize)
     */
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

    /**
     * times, lats, lons are vector of length timeSize, latSize, lonSize respectively.
     * The maintain the following invariant:
     * grid[timeIndex,latIndex,lonIndex] gives the u,v at the point with latitude at lats[latIndex],
     * with longitude at lons[lonIndex], and with time at times[timeIndex].
     */
    std::vector<int> times;
    std::vector<double> lats;
    std::vector<double> lons;

    /**
     * The 3D index into the data. The array is sized by [8761][67][116]
     * @return Velocity at that index
     */
    const Vel& operator[](size_t timeIndex, size_t latIndex, size_t lonIndex) const;

    /**
     * Streams a slice at timeIndex t of the matrix to the outstream given by os
     * @param os outstream
     * @param t index with which to slice matrix
     */
    void streamSlice(std::ostream &os, size_t t);
};

#endif //UVGRID_H
