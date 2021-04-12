#pragma once

#ifndef RAY_H_
#define RAY_H_

#include "vec.h"

struct ray {
   public:
    ray();
    ray(const point &p, const vec &v);

    point origin() const;
    vec direction() const;

    point at(double t) const;

   private:
    point origin_;
    vec direction_;
};

inline ray::ray() : origin_{}, direction_{} {}

inline ray::ray(const point &p, const vec &v) : origin_{p}, direction_{v} {}

inline point ray::origin() const { return origin_; }

inline vec ray::direction() const { return direction_; }

inline point ray::at(double t) const {
    return origin_ + direction_ * t;
}

#endif  // RAY_H_
