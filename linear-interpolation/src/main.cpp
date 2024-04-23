#include "interpolate.h"
#include "Vel.h"
#include <print>
#include <ranges>

using namespace std;

int main() {
    UVGrid uvGrid;
    uvGrid.printSlice(100);

    int N = 10000000;  // Number of points

    int time_start = 0;
    int time_end = 31536000;

    double lat_start = 46.125;
    double lat_end = 62.625;

    double lon_start = -15.875;
    double lon_end = 12.875;

    // Calculate increments
    double lat_step = (lat_end - lat_start) / (N - 1);
    double lon_step = (lon_end - lon_start) / (N - 1);
    int time_step = (time_end - time_start) / (N - 1);

    vector<tuple<int, double, double>> points;

    for(int i = 0; i < N; i++) {
        points.push_back({time_start+time_step*i, lat_start+lat_step*i, lon_start+lon_step*i});
    }

    auto start = std::chrono::high_resolution_clock::now();

    auto x = bilinearInterpolate(uvGrid, points);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(stop - start);

    println("Time taken for {} points was {} seconds", N, duration.count()/1000.);

    // Do something with result in case of optimisation
    double sum = 0;
    for (auto [u,v]: x) {
        sum += u + v;
    }
    println("Sum = {}", sum);

    return 0;
}
