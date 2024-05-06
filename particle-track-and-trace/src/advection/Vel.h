#ifndef VEL_H
#define VEL_H

#include <utility>
#include <stdexcept>
#include <iostream>
#include <format>

class Vel {
public:
    double u; // Eastward Current Velocity in the Water Column
    double v; // Northward Current Velocity in the Water Column

    Vel(double u, double v);
    Vel(const std::pair<double, double>& p);  // Conversion constructor
    Vel& operator=(const std::pair<double, double>& p);

    // Operator + to add two Vel objects
    Vel operator+(const Vel& other) const;

    // Operator += to add another Vel object to this object
    Vel& operator+=(const Vel& other);

    // Operator * to multiply Vel by a scalar, defined as a member template
    template<typename Scalar>
    Vel operator*(Scalar scalar) const {
        return Vel(u * scalar, v * scalar);
    }

    // Operator / to divide Vel by a scalar, defined as a member template
    template<typename Scalar>
    Vel operator/(Scalar scalar) const;

    // Friend declaration for the stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Vel& vel);
};

// Non-member function for scalar multiplication on the left
template<typename Scalar>
Vel operator*(Scalar scalar, const Vel& p) {
    return Vel(p.u * scalar, p.v * scalar);
}

#endif //VEL_H
