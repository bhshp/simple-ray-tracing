#pragma once

#ifndef VEC_H_
#define VEC_H_

#include <iostream>

#include "util.h"

struct vec {
   public:
    vec();
    vec(double _x, double _y, double _z);

    bool near_zero() const;
    double x() const;
    double y() const;
    double z() const;
    double length2() const;
    double length() const;
    vec unit() const;
    vec operator-() const;
    vec operator+(const vec &v) const;
    vec operator-(const vec &v) const;
    vec operator^(const vec &v) const;
    vec operator*(double x) const;
    vec operator/(double x) const;
    double operator*(const vec &v) const;
    double operator[](size_t index) const;

    double &operator[](size_t index);
    vec &operator+=(const vec &v);
    vec &operator-=(const vec &v);
    vec &operator*=(double x);
    vec &operator/=(double x);
    vec &unitize();

    static vec random();
    static vec random(double min, double max);

   private:
    double x_;
    double y_;
    double z_;
};

using point = vec;

vec operator*(double val, const vec &t);

std::ostream &operator<<(std::ostream &os, const vec &v);

vec random_in_unit_sphere();

vec random_in_hemisphere(const vec &v);

vec random_in_unit_disk();

vec reflect(const vec &v, const vec &n);

vec refract(const vec &uv, const vec &n, double ratio);

// Implementation

inline vec::vec(double _x, double _y, double _z) : x_{_x}, y_{_y}, z_{_z} {}

inline vec::vec() : vec{0, 0, 0} {}

inline bool vec::near_zero() const {
    return std::fabs(x()) < eps && std::fabs(y()) < eps && std::fabs(z()) < eps;
}

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

inline double vec::operator[](size_t index) const {
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

inline vec vec::random() {
    return vec::random(0.0, 1.0);
}

inline vec vec::random(double min, double max) {
    return vec{random_double(min, max), random_double(min, max), random_double(min, max)};
}

inline vec operator*(double val, const vec &t) {
    return t * val;
}

inline std::ostream &operator<<(std::ostream &os, const vec &v) {
    return os << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec random_in_unit_sphere() {
    do {
        vec p = vec::random(-1, 1);
        if (p.length2() < 1) {
            return p;
        }
    } while (true);
}

inline vec random_in_hemisphere(const vec &normal) {
    vec in_unit_sphere = random_in_unit_sphere();
    return normal * in_unit_sphere > 0 ? in_unit_sphere : -in_unit_sphere;
}

inline vec random_in_unit_disk() {
    do {
        vec p{random_double(-1, 1), random_double(-1, 1), 0};
        if (p.length2() < 1) {
            return p;
        }
    } while (true);
}

inline vec reflect(const vec &v, const vec &n) {
    return v - (2 * v * n) * n;
}

inline vec refract(const vec &uv, const vec &n, double ratio) {
    double cos_theta = std::min(-uv * n, 1.0);
    vec r_vertical = ratio * (uv + cos_theta * n);
    vec r_parallel = -std::sqrt(1 - r_vertical.length2()) * n;
    return r_vertical + r_parallel;
}

#endif  // VEC_H_
