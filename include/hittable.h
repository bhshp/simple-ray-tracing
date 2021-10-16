#pragma once

#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <optional>  // std::optional

#include "aabb.h"        // aabb
#include "hit_record.h"  // hit_record
#include "ray.h"         // ray

using hit_result_type = std::optional<hit_record>;
using bound_result_type = std::optional<aabb>;

struct hittable {
   public:
    virtual ~hittable();
    virtual bound_result_type bounding_box(double time_0, double time_1) const = 0;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const = 0;
    virtual double pdf_value(const point &origin, const vec &direction) const;
    virtual vec random(const point &origin) const;
};

struct flip_face : public hittable {
   public:
    flip_face(const std::shared_ptr<hittable> &p);
    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;

   private:
    std::shared_ptr<hittable> p_;
};

#endif  // HITTABLE_H_
