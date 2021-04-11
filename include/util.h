#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>
#include <random>

// Const Numbers
const double inf = std::numeric_limits<double>::max() / 2;
const double pi = std::acos(-1.0);

// Util Functions
double sqr(double x);

double deg2rad(double deg);

double random_double();

int color_cast(double c);

#endif  // UTIL_H_
