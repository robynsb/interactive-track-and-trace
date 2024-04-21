#ifndef LINEARINTERPOLATE_VECUTILS_H
#define LINEARINTERPOLATE_VECUTILS_H

#include <mdspan>
#include <print>

template <typename T>
using arr3d = std::mdspan<
        T,
        std::dextents<
                std::size_t,
                3
        >
>;

/**
 * Print contents of vector
 * @tparam T The type of the data inside the vector
 * @param vec The vector to be printed
 */
template <typename T>
void printContentsOfVec(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::print("{} ", element);

    }
    std::println("");
}

/**
 * Print matrix [x,y] for all values arr[t,x,y]
 * @param arr matrix to be printed
 * @param t value to slice matrix with
 */
template <typename T>
void print3DMatrixSlice(const arr3d<T> &arr, int t) {
    for (int x = 0; x < arr.extent(1); x++) {
        for (int y = 0; y < arr.extent(2); y++) {
            std::print("{} ", arr[t,x,y]);
        }
        std::println("");
    }
}

void print3DMatrixSlice(const arr3d<double> &arr, int t);

#endif //LINEARINTERPOLATE_VECUTILS_H
