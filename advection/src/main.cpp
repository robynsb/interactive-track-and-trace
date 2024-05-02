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
            time = 31536001;
        }
    }
    cout << setprecision(8) << latstart << "," << setprecision(8) << lonstart << ",begin" << i << "," << colour << endl;
    cout << setprecision(8) << lat1 << "," << setprecision(8) << lon1 << ",end" << i << "," << colour << endl;
}

void testGridIndexing(const UVGrid *uvGrid) {
    int time = 20000;
    cout << "=== land === (should all give 0)" << endl;
    cout << bilinearinterpolate(*uvGrid, time, 53.80956379699079, -1.6496306344654406) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 55.31428895563707, -2.851581041325997) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 47.71548983067583, -1.8704054037408626) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 56.23521060314398, 8.505979324950573) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 53.135645440244375, 8.505979324950573) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 56.44761278775708, -4.140629303756164) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 52.67625153110339, 0.8978569759455872) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 52.07154079279377, 4.627951041411331) << endl;

    cout << "=== ocean === (should give not 0)" << endl;
    cout << bilinearinterpolate(*uvGrid, time, 47.43923166616274, -4.985451481829083) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 50.68943556852362, -9.306162999561733) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 53.70606799886677, -4.518347647034465) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 60.57987114267971, -12.208262973672621) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 46.532221548197285, -13.408189172582638) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 50.92725094937812, 1.3975824052375256) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 51.4028921682209, 2.4059571950925203) << endl;
    cout << bilinearinterpolate(*uvGrid, time, 53.448445236769004, 0.7996966058017515) << endl;
//    cout << bilinearinterpolate(*uvGrid, time, ) << endl;
}

int main() {
    std::shared_ptr<UVGrid> uvGrid = std::make_shared<UVGrid>();

    uvGrid->streamSlice(cout, 900);

    auto kernelRK4 = RK4AdvectionKernel(uvGrid);

//    You can use https://maps.co/gis/ to visualise these points
    cout << "======= RK4 Integration =======" << endl;
    advectForSomeTime(*uvGrid, kernelRK4, 53.53407391652826, 6.274975037862238, 0, "#ADD8E6");
    advectForSomeTime(*uvGrid, kernelRK4, 53.494053820479365, 5.673454142386921, 1, "#DC143C");
    advectForSomeTime(*uvGrid, kernelRK4, 53.49321966653616, 5.681867022043919, 2, "#50C878");
    advectForSomeTime(*uvGrid, kernelRK4, 53.581548701694324, 6.552600066543153, 3, "#FFEA00");
    advectForSomeTime(*uvGrid, kernelRK4, 53.431446729744124, 5.241592961691523, 4, "#663399");
    advectForSomeTime(*uvGrid, kernelRK4, 53.27913608324572, 4.82094897884165, 5, "#FFA500");
    advectForSomeTime(*uvGrid, kernelRK4, 53.18597595482688, 4.767667388308705, 6, "#008080");
    advectForSomeTime(*uvGrid, kernelRK4, 53.01592078792383, 4.6064205160882, 7, "#FFB6C1");
    advectForSomeTime(*uvGrid, kernelRK4, 52.72816940158886, 4.5853883152993635, 8, "#36454F"); // on land
    advectForSomeTime(*uvGrid, kernelRK4, 52.56142091881038, 4.502661662924255, 9, "#1E90FF"); // Dodger Blue
    advectForSomeTime(*uvGrid, kernelRK4, 52.23202593893584, 4.2825246383181845, 10, "#FFD700"); // Gold
    advectForSomeTime(*uvGrid, kernelRK4, 52.08062567609582, 4.112864890830927, 11, "#6A5ACD"); // Slate Blue
    advectForSomeTime(*uvGrid, kernelRK4, 51.89497719759734, 3.8114033568921686, 12, "#20B2AA"); // Light Sea Green
    advectForSomeTime(*uvGrid, kernelRK4, 51.752848503723634, 3.664177951809339, 13, "#FF69B4"); // Hot Pink
    advectForSomeTime(*uvGrid, kernelRK4, 51.64595756528835, 3.626319993352851, 14, "#800080"); // Purple
    advectForSomeTime(*uvGrid, kernelRK4, 51.55140730645238, 3.4326152213887986, 15, "#FF4500"); // Orange Red
    advectForSomeTime(*uvGrid, kernelRK4, 51.45679776223422, 3.4452813365018384, 16, "#A52A2A"); // Brown
    advectForSomeTime(*uvGrid, kernelRK4, 51.41444662720727, 3.4648562416765363, 17, "#4682B4"); // Steel Blue
    advectForSomeTime(*uvGrid, kernelRK4, 51.37421261203866, 3.2449264214689455, 18, "#FF6347"); // Tomato
    advectForSomeTime(*uvGrid, kernelRK4, 51.29651848898365, 2.9547572241424773, 19, "#008000"); // Green
    advectForSomeTime(*uvGrid, kernelRK4, 51.19705098468974, 2.7647654914530024, 20, "#B8860B"); // Dark Goldenrod
    advectForSomeTime(*uvGrid, kernelRK4, 51.114719857442665, 2.577076679365129, 21, "#FFC0CB"); // Pink
//    advectForSomeTime(*uvGrid, kernelRK4, ,0);

    return 0;
}
