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

#endif  // RAY_H_
