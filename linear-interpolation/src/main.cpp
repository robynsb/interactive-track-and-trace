#include "readdata.h"

#include <vector>

using namespace std;

int main() {
    auto [vec, size] = readHydrodynamicU();

    auto arr = std::mdspan(vec.data(), size);

    print3DMatrixSlice(arr, 100);

    auto [times, lats, longs] = readGrid();
    printContentsOfVec(lats);

    return 0;
}
