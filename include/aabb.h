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

inline aabb::aabb() {}

inline aabb::aabb(const point &a, const point &b) : min_{a},
                                                    max_{b} {}

inline point aabb::min() const { return min_; }

inline point aabb::max() const { return max_; }

inline bool aabb::hit(const ray &r, double t_min, double t_max) const {
    point origin = r.origin();
    vec direction = r.direction();
    for (int i = 0; i < 3; i++) {
        double t_0 = (min_[i] - origin[i]) / direction[i];
        double t_1 = (max_[i] - origin[i]) / direction[i];
        if (direction[i] < 0) {
            std::swap(t_0, t_1);
        }
        t_min = std::max(t_min, t_0);
        t_max = std::min(t_max, t_1);
        if (t_min >= t_max) {
            return false;
        }
    }
    return true;
}

aabb surrounding_box(const aabb &a, const aabb &b);

inline aabb surrounding_box(const aabb &a, const aabb &b) {
    point a_min = a.min(), a_max = a.max();
    point b_min = b.min(), b_max = b.max();
    return aabb{point{std::min(a_min.x(), b_min.x()),
                      std::min(a_min.y(), b_min.y()),
                      std::min(a_min.z(), b_min.z())},
                point{std::max(a_max.x(), b_max.x()),
                      std::max(a_max.y(), b_max.y()),
                      std::max(a_max.z(), b_max.z())}};
}

#endif  // AABB_H_
