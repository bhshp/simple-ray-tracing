#pragma once

#ifndef RAY_H_
#define RAY_H_

#include "vec.h"

struct ray {
   public:
    ray();
    ray(const point &p, const vec &v, double time = 0.0);

    point origin() const;
    vec direction() const;
    double time() const;

    point at(double t) const;

   private:
    point origin_;
    vec direction_;
    double time_;
};

inline ray::ray() : origin_{}, direction_{}, time_{} {}

inline ray::ray(const point &p, const vec &v, double time) : origin_{p}, direction_{v}, time_{time} {}

inline point ray::origin() const { return origin_; }

inline vec ray::direction() const { return direction_; }

inline double ray::time() const { return time_; }

inline point ray::at(double t) const {
    return origin_ + direction_ * t;
}

#endif  // RAY_H_
