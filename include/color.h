#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>  // std::ostream

#include "util.h"  // color_cast
#include "vec.h"   // constructor color(const vec&)

struct color {
   public:
    color();
    color(double r, double g, double b);
    color(const vec &v);

    double r() const;
    double g() const;
    double b() const;

    color operator-() const;

    color operator+(const color &c) const;

    color operator-(const color &c) const;

    color operator*(double x) const;

    color operator/(double x) const;

    color &operator+=(const color &c);

    color &operator-=(const color &c);

    color &operator*=(double x);

    color &operator/=(double x);

   private:
    double r_, g_, b_;
};

color operator+(const color &c, const vec &v);
color operator+(const vec &v, const color &c);
color operator*(double x, const color &c);
std::ostream &operator<<(std::ostream &os, const color &c);

color mix(const color &a, const color &b, double alpha);
color sample_cast(const color &c, int samples);

#endif  // COLOR_H_
