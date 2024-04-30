#include <ranges>
#include <iomanip>
#include <stdexcept>

#include "interpolate.h"
#include "Vel.h"
#include "EulerAdvectionKernel.h"
#include "RK4AdvectionKernel.h"
#include "interpolate.h"

#define NotAKernelError "Template parameter T must derive from AdvectionKernel"

using namespace std;

template <typename AdvectionKernelImpl>
void advectForSomeTime(const UVGrid &uvGrid, const AdvectionKernelImpl &kernel, double latstart, double lonstart, int i, char colour[10]) {

    // Require at compile time that kernel derives from the abstract class AdvectionKernel
    static_assert(std::is_base_of<AdvectionKernel, AdvectionKernelImpl>::value, NotAKernelError);

    double lat1 = latstart, lon1 = lonstart;
    for(int time = 0; time <= 31536000.; time += AdvectionKernel::DT) {
//        cout << setprecision(8) << lat1 << "," << setprecision(8) << lon1 << ",end" << i << "," << colour << endl;
        try {
            auto [templat, templon] = kernel.advect(time, lat1, lon1);
            lat1 = templat;
            lon1 = templon;
        } catch (const out_of_range& e) {
            cerr << "broke out of loop!" << endl;
            break;
        }
    }
    cout << setprecision(8) << latstart << "," << setprecision(8) << lonstart << ",begin" << i << "," << colour << endl;
    cout << setprecision(8) << lat1 << "," << setprecision(8) << lon1 << ",end" << i << "," << colour << endl;
}

void testGridIndexing(const UVGrid *uvGrid) {
    int time = 20000;
    cout << "=== land === (should all give 0)" << endl;
    cout << bilinearinterpolation(*uvGrid, time, 53.80956379699079, -1.6496306344654406) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 55.31428895563707, -2.851581041325997) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 47.71548983067583, -1.8704054037408626) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 56.23521060314398, 8.505979324950573) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 53.135645440244375, 8.505979324950573) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 56.44761278775708, -4.140629303756164) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 52.67625153110339, 0.8978569759455872) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 52.07154079279377, 4.627951041411331) << endl;

    cout << "=== ocean === (should give not 0)" << endl;
    cout << bilinearinterpolation(*uvGrid, time, 47.43923166616274, -4.985451481829083) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 50.68943556852362, -9.306162999561733) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 53.70606799886677, -4.518347647034465) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 60.57987114267971, -12.208262973672621) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 46.532221548197285, -13.408189172582638) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 50.92725094937812, 1.3975824052375256) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 51.4028921682209, 2.4059571950925203) << endl;
    cout << bilinearinterpolation(*uvGrid, time, 53.448445236769004, 0.7996966058017515) << endl;
//    cout << bilinearinterpolation(*uvGrid, time, ) << endl;
}

int main() {
    std::shared_ptr<UVGrid> uvGrid = std::make_shared<UVGrid>();

    uvGrid->streamSlice(cout, 900);

    RK4AdvectionKernel kernelRK4 = RK4AdvectionKernel(uvGrid);

//    You can use https://maps.co/gis/ to visualise these points
    cout << "======= RK4 Integration =======" << endl;
    advectForSomeTime(*uvGrid, kernelRK4, 54.331795276466615, 4.845871408626273, 0, "#ADD8E6");
    advectForSomeTime(*uvGrid, kernelRK4, 59.17208978388813, 0.32865481669722213, 1, "#DC143C");
    advectForSomeTime(*uvGrid, kernelRK4, 56.18661322856813, -9.521463269751877, 2, "#50C878");
    advectForSomeTime(*uvGrid, kernelRK4, 46.6048774007515, -2.8605696406405947, 3, "#FFEA00");
    advectForSomeTime(*uvGrid, kernelRK4, 51.45431808648367, 1.6682437444140332, 4, "#663399");
    advectForSomeTime(*uvGrid, kernelRK4, 51.184757012016085, -6.418923014612084, 5, "#FFA500");
    advectForSomeTime(*uvGrid, kernelRK4, 54.48325546269538, 7.167517140551792, 6, "#008080");
    advectForSomeTime(*uvGrid, kernelRK4, 55.43253322410253, -1.1712503620884716, 7, "#FFB6C1");
    advectForSomeTime(*uvGrid, kernelRK4, 48.852815074172085, 3.4294489497130516, 8, "#36454F"); // on land
    advectForSomeTime(*uvGrid, kernelRK4, 58.02431905976983, 1.6892571305388995, 9, "#1E90FF"); // Dodger Blue
    advectForSomeTime(*uvGrid, kernelRK4, 58.99404571805297, 3.4121513161325425, 10, "#FFD700"); // Gold
    advectForSomeTime(*uvGrid, kernelRK4, 59.51039243098509, -1.6674160241521663, 11, "#6A5ACD"); // Slate Blue
    advectForSomeTime(*uvGrid, kernelRK4, 60.51250220636489, 1.020893006817227, 12, "#20B2AA"); // Light Sea Green
    advectForSomeTime(*uvGrid, kernelRK4, 60.38797801281417, 3.516119068711471, 13, "#FF69B4"); // Hot Pink
    advectForSomeTime(*uvGrid, kernelRK4, 60.02637651315464, -2.4546004365354697, 14, "#800080"); // Purple
    advectForSomeTime(*uvGrid, kernelRK4, 58.732929454411305, 3.649791893455804, 15, "#FF4500"); // Orange Red
//    advectForSomeTime(*uvGrid, kernelRK4, ,0);

    return 0;
}
