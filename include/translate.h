#pragma once

#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include "hittable.h"

struct translate : public hittable {
   public:
    translate(const std::shared_ptr<hittable> &p, const vec &offset);
    virtual ~translate();
    virtual hit_result_type hit(const ray &in, double t_min, double t_max) const override;
    virtual bound_result_type bounding_box(double time_0, double time_1) const override;

   private:
    std::shared_ptr<hittable> p_;
    vec offset_;
};

#endif  // TRANSLATE_H_
