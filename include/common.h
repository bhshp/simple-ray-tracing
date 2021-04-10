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
template <typename T>
color operator*(T val, const color &t);

color operator+(const color &c, const vec &v);
color operator+(const vec &v, const color &c);

// Utils
inline double deg2rad(double deg);
inline color mix(const color &a, const color &b, double alpha);
inline double random_double();

// Initialize And Config
const int width_ratio = 16;
const int height_ratio = 9;

const double aspect_ratio = 1.0 * width_ratio / height_ratio;

const int image_width = 1600;
const int image_height = static_cast<int>(1.0 * image_width / aspect_ratio);

const double viewport_height = 2.0;
const double viewport_width = aspect_ratio * viewport_height;
const double focal_length = 1.0;

const char *const path = "./target/out.ppm";

point origin{0, 0, 0};
point horizontal{viewport_width, 0, 0};
point vertical{0, viewport_height, 0};
point lower_left = origin - (horizontal * 0.5) - (vertical * 0.5) - vec{0, 0, focal_length};

// Implementation
template <typename T>
color operator*(T val, const color &t) {
    return t * val;
}

color operator+(const color &c, const vec &v) {
    return color{c.r() + v.x(), c.g() + v.y(), c.b() + v.z()};
}

color operator+(const vec &v, const color &c) {
    return c + v;
}

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

#endif  // COMMON_H_
