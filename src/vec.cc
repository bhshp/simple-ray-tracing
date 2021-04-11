#include "vec.h"

#include <iostream>

inline vec::vec(double _x, double _y, double _z) : x_{_x}, y_{_y}, z_{_z} {}

inline vec::vec() : vec{0, 0, 0} {}

inline double vec::x() const { return x_; }

inline double vec::y() const { return y_; }

inline double vec::z() const { return z_; }

inline double vec::length2() const {
    return sqr(x_) + sqr(y_) + sqr(z_);
}

inline double vec::length() const {
    return std::sqrt(length2());
}

inline vec vec::unit() const {
    return *this / length();
}

inline vec vec::operator-() const {
    return vec{-x_, -y_, -z_};
}

inline vec vec::operator+(const vec &v) const {
    return vec{x_ + v.x_, y_ + v.y_, z_ + v.z_};
}

inline vec vec::operator-(const vec &v) const {
    return vec{x_ - v.x_, y_ - v.y_, z_ - v.z_};
}

inline vec vec::operator^(const vec &v) const {
    return vec{y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_};
}

inline vec vec::operator*(double x) const {
    return vec{x_ * x, y_ * x, z_ * x};
}

inline vec vec::operator/(double x) const {
    return vec{x_ / x, y_ / x, z_ / x};
}

inline double vec::operator*(const vec &v) const {
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

inline double &vec::operator[](size_t index) {
    switch (index) {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw "now such element";
    }
}

inline vec &vec::operator+=(const vec &v) {
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
}

inline vec &vec::operator-=(const vec &v) {
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
}

inline vec &vec::operator*=(double x) {
    x_ *= x;
    y_ *= x;
    z_ *= x;
    return *this;
}

inline vec &vec::operator/=(double x) {
    x_ /= x;
    y_ /= x;
    z_ /= x;
    return *this;
}

inline vec &vec::unitize() {
    double len = length();
    this->x_ /= len;
    this->y_ /= len;
    this->z_ /= len;
    return *this;
}

inline vec operator*(double val, const vec &t) {
    return t * val;
}

inline std::ostream &operator<<(std::ostream &os, const vec &v) {
    return os << v.x() << ' ' << v.y() << ' ' << v.z();
}
