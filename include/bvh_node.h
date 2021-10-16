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

#endif  // BVH_H_
