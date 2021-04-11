#pragma once

#ifndef VEC_H_
#define VEC_H_

#include "util.h"

struct vec {
   public:
    vec();
    vec(double _x, double _y, double _z);

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

    double &operator[](size_t index);
    vec &operator+=(const vec &v);
    vec &operator-=(const vec &v);
    vec &operator*=(double x);
    vec &operator/=(double x);
    vec &unitize();

   private:
    double x_;
    double y_;
    double z_;
};

using point = vec;

vec operator*(double val, const vec &t);

std::ostream &operator<<(std::ostream &os, const vec &v);

#endif  // VEC_H_
