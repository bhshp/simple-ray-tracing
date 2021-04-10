#pragma once

#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <optional>

#include "hit_record.h"

class hittable {
   public:
    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const = 0;
    virtual ~hittable() {}
};

#endif  // HITTABLE_H_