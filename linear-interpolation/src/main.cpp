#include "interpolate.h"

using namespace std;

int main() {
    UVGrid uvGrid;
    auto p = bilinearInterpolate(uvGrid, {392400, 53, -14.5});

    println("({}, {})", p.first, p.second);
    p = bilinearInterpolate(uvGrid, {802400, 62, -14.5});

    return 0;
}
