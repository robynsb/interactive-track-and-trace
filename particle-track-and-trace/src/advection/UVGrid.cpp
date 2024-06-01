#include <ranges>

#include "UVGrid.h"
#include "readdata.h"


using namespace std;

UVGrid::UVGrid(string path) {
  auto us = readHydrodynamicU(path);
  auto vs = readHydrodynamicV(path);
  if (us.size() != vs.size()) {
    throw domain_error(sizeError2);
  }

  tie(times, lats, lons) = readGrid(path);

  timeSize = times.size();
  latSize = lats.size();
  lonSize = lons.size();

  size_t gridSize = timeSize * latSize * lonSize;
  if (gridSize != us.size()) {
    throw domain_error(sizeError);
  }

  uvData.reserve(gridSize);

  for (auto vel: views::zip(us, vs)) {
    uvData.push_back(Vel(vel));
  }
}

const Vel &UVGrid::operator[](size_t timeIndex, size_t latIndex, size_t lonIndex) const {
  if (timeIndex < 0 or timeIndex >= timeSize
      or latIndex < 0 or latIndex >= latSize
      or lonIndex < 0 or lonIndex >= lonSize) {
    throw std::out_of_range(indexOutOfBounds);
  }
  size_t index = timeIndex * (latSize * lonSize) + latIndex * lonSize + lonIndex;
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

double UVGrid::lonMin() const {
  return this->lons.front();
}

double UVGrid::lonMax() const {
  return this->lons.back();
}

double UVGrid::latMin() const {
  return this->lats.front();
}

double UVGrid::latMax() const {
  return this->lats.back();
}

double UVGrid::timeMax() const {
  return this->times.back();
}

void UVGrid::streamSlice(ostream &os, size_t t) {
  for (int x = 0; x < latSize; x++) {
    for (int y = 0; y < lonSize; y++) {
      auto vel = (*this)[t, x, y];
      os << vel << " ";
    }
    os << endl;
  }
}
