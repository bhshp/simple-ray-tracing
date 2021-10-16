#pragma once

#ifndef ROTATE_H_
#define ROTATE_H_

#include "hittable.h"

struct rotate_y : public hittable {
   public:
    rotate_y(const std::shared_ptr<hittable> &p, double angle);
    ~rotate_y();
    virtual hit_result_type hit(const ray &in, double t_min, double t_max) const override;
    virtual bound_result_type bounding_box(double time_0, double time_1) const override;

   private:
    std::shared_ptr<hittable> p_;
    double radians_;
    double sin_theta_;
    double cos_theta_;
    bound_result_type box_;
};

#endif  // ROTATE_H_
