#pragma once

#ifndef CONSTANT_MEDIUM_H_
#define CONSTANT_MEDIUM_H_

#include "hittable.h"
#include "material.h"
#include "texture.h"

struct constant_medium : public hittable {
   public:
    constant_medium(const std::shared_ptr<hittable> &p, double d, const std::shared_ptr<texture> &t);
    constant_medium(const std::shared_ptr<hittable> &p, double d, const color &c);
    virtual ~constant_medium();
    virtual hit_result_type hit(const ray &in, double t_min, double t_max) const override;
    virtual bound_result_type bounding_box(double time_0, double time_1) const override;

   private:
    std::shared_ptr<hittable> boundary_;
    double neg_inv_density_;
    std::shared_ptr<material> phase_function_;
};

#endif  // CONSTANT_MEDIUM_H_
