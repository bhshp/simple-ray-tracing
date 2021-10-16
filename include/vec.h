#pragma once

#ifndef VEC_H_
#define VEC_H_

#include <iostream>

#include "const.h"

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

vec random_unit_vector();

vec random_cosine_direction();

vec random_to_sphere(double radius, double length2);

vec reflect(const vec &v, const vec &n);

vec refract(const vec &uv, const vec &n, double ratio);

#endif  // VEC_H_
