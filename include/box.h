#pragma once

#ifndef BOX_H_
#define BOX_H_

#include <memory>
#include <optional>

#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "rectangle.h"
#include "vec.h"

struct box : public hittable {
   public:
    box();
    box(const point &p0,
        const point &p1,
        const std::shared_ptr<material> &p);
    virtual ~box();
    virtual hit_result_type hit(const ray &in, double t_min, double t_max) const override;
    virtual bound_result_type bounding_box(double time_0, double time_1) const override;

   private:
    point box_min_;
    point box_max_;
    hittable_list sides_;
};

#endif  // BOX_H_