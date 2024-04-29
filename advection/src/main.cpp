#include "interpolate.h"
#include "Vel.h"
#include "EulerAdvectionKernel.h"
#include "RK4AdvectionKernel.h"
#include <ranges>
#include <chrono>

using namespace std;

int main() {
    std::shared_ptr<UVGrid> uvGrid = std::make_shared<UVGrid>();
//    uvGrid->streamSlice(cout, 100);

    EulerAdvectionKernel kernelEuler = EulerAdvectionKernel(uvGrid);
    RK4AdvectionKernel kernelRK4 = RK4AdvectionKernel(uvGrid);

    double latstart = 54.860801, lonstart = 4.075492;

    double lat1 = latstart, lon1 = lonstart;
    cout << "======= Euler Integration =======" << endl;
    for(int time = 100; time <= 10000; time += DT) {
        cout << "lat = " << lat1 << " lon = " << lon1 << endl;
        auto [templat, templon] = kernelEuler.advect(time, lat1, lon1);
        lat1 = templat;
        lon1 = templon;
    }
    cout << "======= RK4 Integration =======" << endl;
    lat1 = latstart, lon1 = lonstart;
    for(int time = 100; time <= 10000; time += DT) {
        cout << "lat = " << lat1 << " lon = " << lon1 << endl;
        auto [templat, templon] = kernelRK4.advect(time, lat1, lon1);
        lat1 = templat;
        lon1 = templon;
    }

    return 0;
}
