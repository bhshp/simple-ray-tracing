#include "ray.h"

#include "vec.h"

inline ray::ray() : origin_{}, direction_{} {}

inline ray::ray(const point &p, const vec &v) : origin_{p}, direction_{v} {}

inline point ray::origin() const { return origin_; }

inline vec ray::direction() const { return direction_; }

inline point ray::at(double t) const {
    return origin_ + direction_ * t;
}
