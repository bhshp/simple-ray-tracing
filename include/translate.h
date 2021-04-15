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

translate::translate(const std::shared_ptr<hittable> &p, const vec &offset) : p_{p}, offset_{offset} {}

translate::~translate() {}

hit_result_type translate::hit(const ray &in, double t_min, double t_max) const {
    ray move_ray{in.origin() - offset_, in.direction(), in.time()};
    if (hit_result_type rec = p_->hit(move_ray, t_min, t_max); rec.has_value()) {
        point p = rec->p() + offset_;
        vec normal = rec->normal();
        bool front_face = move_ray.direction() * normal < 0;
        if (!front_face) {
            normal = -normal;
        }
        return std::make_optional<hit_record>(rec->t(), p, normal, front_face, rec->mat(), rec->u(), rec->v());
    }
    return std::nullopt;
}

bound_result_type translate::bounding_box(double time_0, double time_1) const {
    if (bound_result_type res = p_->bounding_box(time_0, time_1); res.has_value()) {
        return std::make_optional<aabb>(res->min() + offset_, res->max() + offset_);
    }
    return std::nullopt;
}

#endif  // TRANSLATE_H_
