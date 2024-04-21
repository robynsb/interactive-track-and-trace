#include "point.h"

point operator+(const point& p1, const point& p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

point& operator+=(point& p1, const point& p2) {
    p1.first += p2.first;
    p1.second += p2.second;
    return p1;
}