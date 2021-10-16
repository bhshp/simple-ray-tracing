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

#endif  // UTIL_H_
