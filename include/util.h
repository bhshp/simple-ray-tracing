#ifndef UTIL_H_
#define UTIL_H_

#include <cassert>
#include <cmath>
#include <limits>
#include <random>

#include "vec.h"

// Const Numbers
extern const double inf;
extern const double pi;
extern const double eps;

// Util Functions
double sqr(double x);

double deg2rad(double deg);

int random_int();

int random_int(int a, int b);

double random_double();

double random_double(double a, double b);

int color_cast(double c);

double clamp(double a, double min, double max);

int clamp(int a, int min, int max);

// Implementations

extern const double inf = std::numeric_limits<double>::infinity();
extern const double pi = std::acos(-1.0);
extern const double eps = 1e-8;

inline double sqr(double x) {
    return x * x;
}

inline double deg2rad(double deg) {
    return deg / 180.0 * pi;
}

inline int random_int(int a, int b) {
    static std::mt19937_64 gen{std::random_device{}()};
    return std::uniform_int_distribution<int>{a, b}(gen);
}

inline double random_double() {
    return random_double(0.0, 1.0);
}

inline double random_double(double a, double b) {
    static std::mt19937_64 gen{std::random_device{}()};
    return std::uniform_real_distribution<double>{a, b}(gen);
}

inline int color_cast(double c) {
    if (std::isnan(c)) {
        return 0;
    } else if (c > 0 && c < 1) {
        return static_cast<int>(c * 256.0);
    }
    return c <= 0 ? 0 : 255;
}

inline double clamp(double a, double min, double max) {
    if (a > min && a < max) {
        return a;
    }
    return a <= min ? min : max;
}

inline int clamp(int a, int min, int max) {
    if (a > min && a < max) {
        return a;
    }
    return a <= min ? min : max;
}

#endif  // UTIL_H_
