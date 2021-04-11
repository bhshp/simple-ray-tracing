#pragma once

#ifndef COMMON_H_
#define COMMON_H_

#include <cmath>
#include <limits>
#include <random>

#include "color.h"
#include "hit_record.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec.h"

// Alias
using result_type = std::optional<hit_record>;

// Const Numbers
const double inf = std::numeric_limits<double>::max() / 2;
const double pi = std::acos(-1.0);

// Operators
inline color operator+(const color &c, const vec &v);
inline color operator+(const vec &v, const color &c);
template <typename T>
inline color operator*(T val, const color &t);
std::ostream &operator<<(std::ostream &os, const color &c);

// Utils
inline double deg2rad(double deg);
inline color mix(const color &a, const color &b, double alpha);
inline double random_double();
inline int color_cast(double c);

// Initialize And Config
const char *const path = "./target/out.ppm";

// Operator Implementation
color operator+(const color &c, const vec &v) {
    return color{c.r() + v.x(), c.g() + v.y(), c.b() + v.z()};
}

color operator+(const vec &v, const color &c) {
    return c + v;
}

template <typename T>
color operator*(T val, const color &t) {
    return t * val;
}

std::ostream &operator<<(std::ostream &os, const color &c) {
    return os << color_cast(c.r()) << ' ' << color_cast(c.g()) << ' ' << color_cast(c.b());
}

// Util Implementation
inline double deg2rad(double deg) {
    return deg / 180.0 * pi;
}

inline color mix(const color &a, const color &b, double alpha) {
    return (1.0 - alpha) * a + alpha * b;
}

inline double random_double() {
    static std::mt19937_64 gen{std::random_device{}()};
    static std::uniform_real_distribution<double> dis{0.0, 1.0};
    return dis(gen);
}

inline int color_cast(double c) {
    if (c <= 0) {
        return 0;
    } else if (c >= 1.0) {
        return 255;
    }
    return static_cast<int>(c * 256.0);
}

inline color sample_cast(const color &c, int samples) {
    return c / samples;
}

#endif  // COMMON_H_
