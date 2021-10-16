#pragma once

#ifndef AABB_H_
#define AABB_H_

#include "ray.h"
#include "vec.h"

struct aabb {
   public:
    aabb();
    aabb(const point &a, const point &b);

    bool hit(const ray &r, double t_min, double t_max) const;

    point min() const;
    point max() const;

   private:
    point min_;
    point max_;
};

aabb surrounding_box(const aabb &a, const aabb &b);

#endif  // AABB_H_
