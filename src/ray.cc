#include "ray.h"

ray::ray() : origin_{}, direction_{}, time_{} {}

ray::ray(const point &p, const vec &v, double time) : origin_{p}, direction_{v}, time_{time} {}

point ray::origin() const { return origin_; }

vec ray::direction() const { return direction_; }

double ray::time() const { return time_; }

point ray::at(double t) const {
    return origin_ + direction_ * t;
}
