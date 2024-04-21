#include <print>

#include "vecutils.h"

using namespace std;

void print3DMatrixSlice(const arr3d<double> &arr, int t) {
    for (int x = 0; x < arr.extent(1); x++) {
        for (int y = 0; y < arr.extent(2); y++) {
            print("{:>10.4f} ", arr[t,x,y]);
        }
        println("");
    }
}

void print3DMatrixSlice(const arr3d<std::pair<double, double>> &arr, int t) {
    for (int x = 0; x < arr.extent(1); x++) {
        for (int y = 0; y < arr.extent(2); y++) {
            auto [u,v] = arr[t,x,y];
            print("({:>7.4f}, {:>7.4f}) ", u, v);
        }
        println("");
    }
}
