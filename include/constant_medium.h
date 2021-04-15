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

constant_medium::constant_medium(const std::shared_ptr<hittable> &p, double d, const std::shared_ptr<texture> &t) : boundary_{p},
                                                                                                                    neg_inv_density_{-1.0 / d},
                                                                                                                    phase_function_{std::make_shared<isotropic>(t)} {}

constant_medium::constant_medium(const std::shared_ptr<hittable> &p, double d, const color &c) : boundary_{p},
                                                                                                 neg_inv_density_{-1.0 / d},
                                                                                                 phase_function_{std::make_shared<isotropic>(c)} {}

constant_medium::~constant_medium() {}

hit_result_type constant_medium::hit(const ray &in, double t_min, double t_max) const {
    double t_1, t_2;
    if (hit_result_type rec = boundary_->hit(in, -inf, inf); rec.has_value()) {
        t_1 = rec->t();
    } else {
        return std::nullopt;
    }
    if (hit_result_type rec = boundary_->hit(in, t_1 + eps, inf); rec.has_value()) {
        t_1 = std::max(t_1, t_min);
        t_2 = std::min(t_max, rec->t());
        if (t_1 >= t_2) {
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }
    t_1 = std::max(t_1, 0.0);
    const double ray_length = in.direction().length();
    const double distance_inside_boundary = (t_2 - t_1) * ray_length;
    const double hit_distance = neg_inv_density_ * std::log(random_double());
    if (hit_distance > distance_inside_boundary) {
        return std::nullopt;
    }
    double t = t_1 + hit_distance / ray_length;
    point p = in.at(t);
    return std::make_optional<hit_record>(t, p, vec{}, true, phase_function_);
}

bound_result_type constant_medium::bounding_box(double time_0, double time_1) const {
    return boundary_->bounding_box(time_0, time_1);
}

#endif  // CONSTANT_MEDIUM_H_
