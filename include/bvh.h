#pragma once

#ifndef BVH_H_
#define BVH_H_

#include <vector>

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

struct bvh_node : public hittable {
   public:
    bvh_node();

    bvh_node(std::vector<std::shared_ptr<hittable>> &list,
             std::vector<std::shared_ptr<hittable>>::const_iterator begin,
             std::vector<std::shared_ptr<hittable>>::const_iterator end,
             double time_0,
             double time_1);

    bvh_node(std::vector<std::shared_ptr<hittable>> list,
             double time_0,
             double time_1);

    bvh_node(const hittable_list &list,
             double time_0,
             double time_1);

    virtual ~bvh_node();

    virtual std::optional<hit_record> hit(const ray &r, double t_min, double t_max) const;

    virtual std::optional<aabb> bounding_box(double time_0, double time_1) const;

   private:
    std::shared_ptr<hittable> left_;
    std::shared_ptr<hittable> right_;
    aabb box_;
};

bvh_node::bvh_node() {}

bvh_node::bvh_node(const hittable_list &objects_list,
                   double time_0,
                   double time_1) : bvh_node{objects_list.list(), time_0, time_1} {}

bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> objects_list,
                   double time_0,
                   double time_1) : bvh_node{
                                        objects_list,
                                        objects_list.cbegin(),
                                        objects_list.cend(),
                                        time_0,
                                        time_1} {}

bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> &list,
                   std::vector<std::shared_ptr<hittable>>::const_iterator begin,
                   std::vector<std::shared_ptr<hittable>>::const_iterator end,
                   double time_0,
                   double time_1) {
    static auto comparator = [](const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b) -> bool {
        if (std::optional<aabb> box_a = a->bounding_box(0, 0), box_b = b->bounding_box(0, 0);
            box_a != std::nullopt && box_b != std::nullopt) {
            point a = box_a->min(), b = box_b->min();
            for (int i = 0; i < 3; i++) {
                if (a[i] != b[i]) {
                    return a[i] < b[i];
                }
            }
            return true;
        }
        throw "No Bounding Box in bvh_node constructor";
    };
    if (begin >= end) {
        return;
    }
    std::vector<std::shared_ptr<hittable>>::const_iterator mid = begin + (end - begin) / 2;
    std::nth_element(begin, mid, end, comparator);
    left_ = std::make_shared<bvh_node>(list, begin, mid, time_0, time_1);
    right_ = std::make_shared<bvh_node>(list, mid, end, time_0, time_1);
    if (std::optional<aabb> box_l = left_->bounding_box(0, 0), box_r = right_->bounding_box(0, 0);
        box_l != std::nullopt && box_r != std::nullopt) {
        box_ = surrounding_box(box_l.value(), box_r.value());
    }
    throw "No Bounding Box in bvh_node constructor";
}

bvh_node::~bvh_node() {}

std::optional<hit_record> bvh_node::hit(const ray &r, double t_min, double t_max) const {
    if (!box_.hit(r, t_min, t_max)) {
        return std::nullopt;
    }
    std::optional<hit_record> left_hit_record = left_->hit(r, t_min, t_max);
    std::optional<hit_record> right_hit_record = right_->hit(r, t_min, t_max);
    return left_hit_record.has_value() ? left_hit_record : right_hit_record;
}

std::optional<aabb> bvh_node::bounding_box(double time_0, double time_1) const {
    return std::make_optional<aabb>(box_);
}

#endif  // BVH_H_
