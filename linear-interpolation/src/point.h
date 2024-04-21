#ifndef LINEARINTERPOLATE_POINT_H
#define LINEARINTERPOLATE_POINT_H

#include <utility>

using point = std::pair<double, double>; // {u, v}

point operator+(const point& p1, const point& p2);

point& operator+=(point& p1, const point& p2);

template<typename Scalar>
point operator*(const point& p, Scalar scalar) {
    return {p.first * scalar, p.second * scalar};
}

template<typename Scalar>
point operator*(Scalar scalar, const point& p) {
    return {p.first * scalar, p.second * scalar};
}

template<typename Scalar>
point operator/(const point& p, Scalar scalar) {
    return {p.first / scalar, p.second / scalar};
}

#endif //LINEARINTERPOLATE_POINT_H
