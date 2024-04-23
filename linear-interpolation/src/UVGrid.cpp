#include <ranges>

#include "UVGrid.h"
#include "readdata.h"
#include "to_vector.h"

#define sizeError2 "The sizes of the hydrodynamic data files are different"
#define sizeError "The sizes of the hydrodynamicU or -V files does not correspond with the sizes of the grid file"

using namespace std;

UVGrid::UVGrid() {
    auto us = readHydrodynamicU();
    auto vs = readHydrodynamicV();
    if (us.size() != vs.size()) {
        throw domain_error(sizeError2);
    }

    tie(times, lats, lons) = readGrid();

    timeSize = times.size();
    latSize = lats.size();
    lonSize = lons.size();

    size_t gridSize = timeSize * latSize * lonSize;
    if (gridSize != us.size()) {
        throw domain_error(sizeError);
    }

  uvData = to_vector(views::transform(views::zip(us, vs), [](auto pair){return Vel(pair);}));
//     uvData = views::zip(us, vs)
//              | views::transform([](auto pair) {
//         return Vel(pair);
//     })
// | ranges::to<vector>();
}

const Vel &UVGrid::operator[](size_t timeIndex, size_t latIndex, size_t lonIndex) const {
    size_t index = timeIndex * (latSize * lonSize) + latIndex * lonIndex + lonIndex;
    return uvData[index];
}

double UVGrid::lonStep() const {
    return lons[1] - lons[0];
}

double UVGrid::latStep() const {
    return lats[1] - lats[0];
}

int UVGrid::timeStep() const {
    return times[1] - times[0];
}

void UVGrid::printSlice(size_t t) {
    for (int x = 0; x < latSize; x++) {
        for (int y = 0; y < lonSize; y++) {
            auto [u,v] = (*this)[t,x,y];
            printf("%7.4f, %7.4f", u, v);
        }
      cout << endl;
    }
}