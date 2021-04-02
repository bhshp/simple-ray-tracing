#pragma once

#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

struct ray {
   public:
    ray(const point &p, const vec3 &v) : origin_{p}, direction_{v} {}
    ray() : origin_{}, direction_{} {}

    point origin() const { return origin_; }
    vec3 direction() const { return direction_; }

    point at(double t) const {
        return origin_ + direction_ * t;
    }

   private:
    point origin_;
    vec3 direction_;
};

#endif  // RAY_H_
