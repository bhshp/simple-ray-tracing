#pragma once

#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <optional>  // std::optional

#include "aabb.h"        // aabb
#include "hit_record.h"  // hit_record
#include "ray.h"         // ray

using hit_result_type = std::optional<hit_record>;

class hittable {
   public:
    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const = 0;

    virtual std::optional<aabb> bounding_box(double time_0, double time_1) const = 0;

    virtual ~hittable();
};

inline hittable::~hittable() {}

#endif  // HITTABLE_H_
