#include "box.h"

box::box() {}

box::box(const point &p0, const point &p1, const std::shared_ptr<material> &ptr) : box_min_{p0}, box_max_{p1} {
    sides_.push_back(std::make_shared<xy_rectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
    sides_.push_back(std::make_shared<xy_rectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));

    sides_.push_back(std::make_shared<xz_rectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
    sides_.push_back(std::make_shared<xz_rectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));

    sides_.push_back(std::make_shared<yz_rectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
    sides_.push_back(std::make_shared<yz_rectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
}

box::~box() {}

hit_result_type box::hit(const ray &in, double t_min, double t_max) const {
    return sides_.hit(in, t_min, t_max);
}

bound_result_type box::bounding_box(double, double) const {
    return std::make_optional<aabb>(box_min_, box_max_);
}
