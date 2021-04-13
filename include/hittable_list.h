#pragma once

#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include <memory>  // std::shared_ptr
#include <vector>  // std::vector

#include "hit_record.h"  // hit_record
#include "hittable.h"    // hittable

struct hittable_list : public hittable {
   public:
    hittable_list();
    virtual ~hittable_list();

    const std::vector<std::shared_ptr<hittable>> &list() const;

    void push_back(const std::shared_ptr<hittable> &object);
    void pop_back();
    void clear();

    virtual std::optional<hit_record> hit(const ray &r, double t_min, double t_max) const override;

    virtual std::optional<aabb> bounding_box(double time_0, double time_1) const override;

   private:
    std::vector<std::shared_ptr<hittable>> list_;
};

inline hittable_list::hittable_list() {}

inline hittable_list::~hittable_list() {}

inline const std::vector<std::shared_ptr<hittable>> &hittable_list::list() const {
    return list_;
}

inline void hittable_list::push_back(const std::shared_ptr<hittable> &object) {
    list_.push_back(object);
}

inline void hittable_list::pop_back() {
    list_.pop_back();
}

inline void hittable_list::clear() {
    list_.clear();
}

inline std::optional<hit_record> hittable_list::hit(const ray &r, double t_min, double t_max) const {
    std::optional<hit_record> result;
    double closest_so_far = t_max;
    for (const std::shared_ptr<hittable> &o : list_) {
        if (std::optional<hit_record> temp = o->hit(r, t_min, closest_so_far); temp.has_value()) {
            closest_so_far = temp->t();
            result = temp;
        }
    }
    return result;
}

inline std::optional<aabb> hittable_list::bounding_box(double time_0, double time_1) const {
    if (list_.empty()) {
        return std::nullopt;
    }
    std::optional<aabb> res;
    for (const std::shared_ptr<hittable> &o : list_) {
        if (std::optional<aabb> bound_res = o->bounding_box(time_0, time_1); bound_res.has_value()) {
            if (res.has_value()) {
                res = surrounding_box(res.value(), bound_res.value());
            } else {
                res = bound_res.value();
            }
        } else {
            return std::nullopt;
        }
    }
    return res;
}

#endif  // HITTABLE_LIST_H_
