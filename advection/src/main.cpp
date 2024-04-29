#include "interpolate.h"
#include "Vel.h"
#include "EulerAdvectionKernel.h"
#include "RK4AdvectionKernel.h"
#include <ranges>
#include <chrono>

#define NotAKernelError "Template parameter T must derive from AdvectionKernel"

using namespace std;

template <typename AdvectionKernelImpl>
void advectForSomeTime(const UVGrid &uvGrid, const AdvectionKernelImpl &kernel, double latstart, double lonstart) {

    // Require at compile time that kernel derives from the abstract class AdvectionKernel
    static_assert(std::is_base_of<AdvectionKernel, AdvectionKernelImpl>::value, NotAKernelError);

    double lat1 = latstart, lon1 = lonstart;
    for(int time = 100; time <= 10000; time += AdvectionKernel::DT) {
        cout << "lat = " << lat1 << " lon = " << lon1 << endl;
        auto [templat, templon] = kernel.advect(time, lat1, lon1);
        lat1 = templat;
        lon1 = templon;
    }
}


int main() {
    std::shared_ptr<UVGrid> uvGrid = std::make_shared<UVGrid>();

    EulerAdvectionKernel kernelEuler = EulerAdvectionKernel(uvGrid);

    RK4AdvectionKernel kernelRK4 = RK4AdvectionKernel(uvGrid);

    double latstart = 52.881770, lonstart = 3.079979;

    cout << "======= Euler Integration =======" << endl;
    advectForSomeTime(*uvGrid, kernelEuler, latstart, lonstart);
    cout << "======= RK4 Integration =======" << endl;
    advectForSomeTime(*uvGrid, kernelRK4, latstart, lonstart);

    return 0;
}
