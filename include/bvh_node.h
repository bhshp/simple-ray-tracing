#pragma once

#ifndef BVH_H_
#define BVH_H_

#include <algorithm>
#include <vector>

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

struct bvh_node : public hittable {
   public:
    bvh_node();

    bvh_node(std::vector<std::shared_ptr<hittable>> &list,
             size_t begin,
             size_t end,
             double time_0 = 0,
             double time_1 = 0);

    bvh_node(std::vector<std::shared_ptr<hittable>> list,
             double time_0 = 0,
             double time_1 = 0);

    bvh_node(const hittable_list &list,
             double time_0 = 0,
             double time_1 = 0);

    virtual ~bvh_node();

    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const;

    virtual bound_result_type bounding_box(double time_0, double time_1) const;

   private:
    std::shared_ptr<hittable> left_;
    std::shared_ptr<hittable> right_;
    aabb box_;
};

hittable_list bvh(const hittable_list &list, double a = 0, double b = 0);

// Implementation

inline bvh_node::bvh_node() {}

inline bvh_node::bvh_node(const hittable_list &objects_list,
                          double time_0,
                          double time_1) : bvh_node{objects_list.list(), time_0, time_1} {}

inline bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> objects_list,
                          double time_0,
                          double time_1) : bvh_node{objects_list,
                                                    0,
                                                    objects_list.size(),
                                                    time_0,
                                                    time_1} {}

inline bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> &list,
                          size_t begin,
                          size_t end,
                          double time_0,
                          double time_1) {
    if (begin >= end) {
        return;
    }
    const int choose = random_int(0, 2);
    auto cmp = [choose](const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b) -> bool {
        if (bound_result_type box_a = a->bounding_box(0, 0), box_b = b->bounding_box(0, 0);
            box_a != std::nullopt && box_b != std::nullopt) {
            return box_a->min()[choose] < box_b->min()[choose];
        }
        std::cerr << "No Bounding Box in bvh_node constructor" << std::endl;
        throw;
    };
    if (end - begin == 1) {
        left_ = right_ = list[begin];
    } else if (end - begin == 2) {
        left_ = list[begin];
        right_ = list[begin + 1];
        if (!cmp(list[begin], list[begin + 1])) {
            std::swap(left_, right_);
        }
    } else {
        size_t mid = begin + (end - begin) / 2;
        std::nth_element(list.begin() + begin, list.begin() + mid, list.begin() + end, cmp);
        left_ = std::make_shared<bvh_node>(list, begin, mid, time_0, time_1);
        right_ = std::make_shared<bvh_node>(list, mid, end, time_0, time_1);
    }
    if (bound_result_type box_l = left_->bounding_box(0, 0), box_r = right_->bounding_box(0, 0);
        box_l != std::nullopt && box_r != std::nullopt) {
        box_ = surrounding_box(box_l.value(), box_r.value());
    } else {
        std::cerr << "No Bounding Box in bvh_node constructor" << std::endl;
        throw;
    }
}

inline bvh_node::~bvh_node() {}

inline hit_result_type bvh_node::hit(const ray &r, double t_min, double t_max) const {
    if (!box_.hit(r, t_min, t_max)) {
        return std::nullopt;
    }
    hit_result_type left_hit_record = left_->hit(r, t_min, t_max);
    hit_result_type right_hit_record = right_->hit(r, t_min,
                                                             left_hit_record.has_value()
                                                                 ? left_hit_record->t()
                                                                 : t_max);
    return right_hit_record.has_value() ? right_hit_record : left_hit_record;
}

inline bound_result_type bvh_node::bounding_box(double, double) const {
    return std::make_optional<aabb>(box_);
}

inline hittable_list bvh(const hittable_list &list, double a, double b) {
    hittable_list world;
    world.push_back(std::make_shared<bvh_node>(list, a, b));
    return world;
}

#endif  // BVH_H_
