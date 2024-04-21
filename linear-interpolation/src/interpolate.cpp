#include <cmath>

#include <ranges>
#include "interpolate.h"

using namespace std;

// Inspired by https://numerical.recipes/book.html Chapter 3.6
point bilinearInterpolate(const UVGrid &uvGrid, std::tuple<int, double, double> timeLatLon) {
    auto [time, lat, lon] = timeLatLon;

    double latStep = uvGrid.latStep();
    double lonStep = uvGrid.lonStep();
    int timeStep = uvGrid.timeStep();

    int latIndex = (lat-uvGrid.lats[0])/latStep;
    int lonIndex = (lon-uvGrid.lons[0])/lonStep;
    int timeIndex = (time-uvGrid.times[0])/timeStep;

    double timeRatio = (static_cast<double>(time)-uvGrid.times[timeIndex])/timeStep;
    double latRatio = (lat-uvGrid.lats[latIndex]) / latStep;
    double lonRatio = (lon-uvGrid.lons[lonIndex]) / lonStep;

    point point = {0, 0};
    for(int time = 0; time <= 1; time++) {
        for(int lat = 0; lat <= 1; lat++) {
            for(int lon = 0; lon <= 1; lon++) {
                auto vertex = uvGrid.uvMatrix[
                        timeIndex + time < uvGrid.uvMatrix.extent(0) ? timeIndex + 1 : timeIndex,
                        latIndex + lat < uvGrid.uvMatrix.extent(1) ? latIndex + 1 : latIndex,
                        lonIndex + lon < uvGrid.uvMatrix.extent(2) ? lonIndex + 1 : lonIndex
                ];

                double timeRation = (1 - time)*(1-timeRatio) + time*timeRatio;
                double latRation = (1 - lat)*(1-latRatio) + lat*latRatio;
                double lonRation = (1 - lon)*(1-lonRatio) + lon*lonRatio;
                point += timeRation * latRation * lonRation * vertex;
            }
        }
    }

    return point;
}
