#include <mdspan>
#include <ranges>

#include "UVGrid.h"
#include "readdata.h"

using namespace std;

UVGrid::UVGrid() {
    auto [us, sizeU] = readHydrodynamicU();
    auto [vs, sizeV] = readHydrodynamicV();
    // Assuming sizeU == sizeV
    uvData = views::zip(us, vs) | ranges::to<vector>();
    uvMatrix = mdspan(uvData.data(), sizeU);
    tie(times, lats, lons) = readGrid();
}

double UVGrid::lonStep() const {
    return lons[1] - lons[0];
}

double UVGrid::latStep() const {
    return lats[1]-lats[0];
}

int UVGrid::timeStep() const {
    return times[1]-times[0];
}