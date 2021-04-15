#pragma once

#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <optional>  // std::optional

#include "aabb.h"        // aabb
#include "hit_record.h"  // hit_record
#include "ray.h"         // ray

using hit_result_type = std::optional<hit_record>;
using bound_result_type = std::optional<aabb>;

class hittable {
   public:
    virtual hit_result_type hit(const ray& r, double t_min, double t_max) const = 0;

    virtual bound_result_type bounding_box(double time_0, double time_1) const = 0;

    virtual ~hittable();
};

inline hittable::~hittable() {}

#endif  // HITTABLE_H_
