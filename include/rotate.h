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

rotate_y::rotate_y(const std::shared_ptr<hittable> &p, double angle) : p_{p},
                                                                       radians_{deg2rad(angle)},
                                                                       sin_theta_{std::sin(radians_)},
                                                                       cos_theta_{std::cos(radians_)},
                                                                       box_{p->bounding_box(0, 1)} {
    point min{inf, inf, inf};
    point max{-inf, -inf, -inf};
    point box_max = box_->max();
    point box_min = box_->min();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * box_max.x() + (1 - i) * box_min.x();
                double y = j * box_max.y() + (1 - j) * box_min.y();
                double z = k * box_max.z() + (1 - k) * box_min.z();
                vec temp{cos_theta_ * x + sin_theta_ * z, y, -sin_theta_ * x + cos_theta_ * z};
                for (int l = 0; l < 3; l++) {
                    min[l] = std::min(min[l], temp[l]);
                    max[l] = std::max(max[l], temp[l]);
                }
            }
        }
    }
    if (box_.has_value()) {
        box_ = std::make_optional<aabb>(min, max);
    }
}

rotate_y::~rotate_y() {}

hit_result_type rotate_y::hit(const ray &in, double t_min, double t_max) const {
    point origin = in.origin();
    vec direction = in.direction();
    origin[0] = cos_theta_ * in.origin()[0] - sin_theta_ * in.origin()[2];
    origin[2] = sin_theta_ * in.origin()[0] + cos_theta_ * in.origin()[2];
    direction[0] = cos_theta_ * in.direction()[0] - sin_theta_ * in.direction()[2];
    direction[2] = sin_theta_ * in.direction()[0] + cos_theta_ * in.direction()[2];
    ray rotate{origin, direction, in.time()};
    if (hit_result_type rec = p_->hit(rotate, t_min, t_max); rec.has_value()) {
        point p = rec->p();
        vec normal = rec->normal();
        p[0] = cos_theta_ * rec->p()[0] + sin_theta_ * rec->p()[2];
        p[2] = -sin_theta_ * rec->p()[0] + cos_theta_ * rec->p()[2];
        normal[0] = cos_theta_ * rec->normal()[0] + sin_theta_ * rec->normal()[2];
        normal[2] = -sin_theta_ * rec->normal()[0] + cos_theta_ * rec->normal()[2];
        bool front_face = rotate.direction() * normal < 0;
        if (!front_face) {
            normal = -normal;
        }
        return std::make_optional<hit_record>(rec->t(), p, normal, front_face, rec->mat(), rec->u(), rec->v());
    }
    return std::nullopt;
}

bound_result_type rotate_y::bounding_box(double, double) const {
    return box_;
}

#endif  // ROTATE_H_
