#include "hittable.h"

hittable::~hittable() {}

double hittable::pdf_value(const point &, const vec &) const {
    return 0;
}

vec hittable::random(const point &) const {
    return vec{1, 0, 0};
}

flip_face::flip_face(const std::shared_ptr<hittable> &p) : p_{p} {}

bound_result_type flip_face::bounding_box(double time_0, double time_1) const {
    return p_->bounding_box(time_0, time_1);
}

hit_result_type flip_face::hit(const ray &r, double t_min, double t_max) const {
    if (hit_result_type rec = p_->hit(r, t_min, t_max); rec.has_value()) {
        return hit_result_type{
            std::in_place,
            rec->t(),
            rec->p(),
            rec->normal(),
            !rec->front_face(),
            rec->mat(),
            rec->u(),
            rec->v()};
    }
    return std::nullopt;
}
