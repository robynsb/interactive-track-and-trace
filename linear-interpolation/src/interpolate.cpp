#include <cmath>
#include <ranges>

#include "interpolate.h"
#include "to_vector.h"

using namespace std;

Vel bilinearInterpolate(const UVGrid &uvGrid, int time, double lat, double lon) {
    double latStep = uvGrid.latStep();
    double lonStep = uvGrid.lonStep();
    int timeStep = uvGrid.timeStep();

    int latIndex = (lat - uvGrid.lats[0]) / latStep;
    int lonIndex = (lon - uvGrid.lons[0]) / lonStep;
    int timeIndex = (time - uvGrid.times[0]) / timeStep;

    double timeRatio = (static_cast<double>(time) - uvGrid.times[timeIndex]) / timeStep;
    double latRatio = (lat - uvGrid.lats[latIndex]) / latStep;
    double lonRatio = (lon - uvGrid.lons[lonIndex]) / lonStep;

    Vel point = {0, 0};
    for (int timeOffset = 0; timeOffset <= 1; timeOffset++) {
        for (int latOffset = 0; latOffset <= 1; latOffset++) {
            for (int lonOffset = 0; lonOffset <= 1; lonOffset++) {
                auto vertex = uvGrid[
                        timeIndex + 1 < uvGrid.timeSize ? timeIndex + timeOffset : timeIndex,
                                latIndex + 1 < uvGrid.latSize ? latIndex + latOffset : latIndex,
                                lonIndex + 1 < uvGrid.lonSize ? lonIndex + lonOffset : lonIndex
                ];

                double timeRation = (1 - timeOffset) * (1 - timeRatio) + timeOffset * timeRatio;
                double latRation = (1 - latOffset) * (1 - latRatio) + latOffset * latRatio;
                double lonRation = (1 - lonOffset) * (1 - lonRatio) + lonOffset * lonRatio;
                point += timeRation * latRation * lonRation * vertex;
            }
        }
    }

    return point;
}

vector<Vel> bilinearInterpolate(const UVGrid &uvGrid, vector<tuple<int, double, double>> points) {
    auto results = points | std::views::transform([&uvGrid](const auto &point) {
        auto [time, lat, lon] = point;
        return bilinearInterpolate(uvGrid, time, lat, lon);
    });
    return to_vector(results);
}
