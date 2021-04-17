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

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;
    virtual double pdf_value(const point &origin, const vec &direction) const override;
    virtual vec random(const point &origin) const override;

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

inline hit_result_type hittable_list::hit(const ray &r, double t_min, double t_max) const {
    hit_result_type result;
    double closest_so_far = t_max;
    for (const std::shared_ptr<hittable> &o : list_) {
        if (hit_result_type temp = o->hit(r, t_min, closest_so_far); temp.has_value()) {
            closest_so_far = temp->t();
            result = temp;
        }
    }
    return result;
}

inline bound_result_type hittable_list::bounding_box(double time_0, double time_1) const {
    if (list_.empty()) {
        return std::nullopt;
    }
    bound_result_type res;
    for (const std::shared_ptr<hittable> &o : list_) {
        if (bound_result_type bound_res = o->bounding_box(time_0, time_1); bound_res.has_value()) {
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

inline double hittable_list::pdf_value(const point &origin, const vec &direction) const {
    double weight = 1.0 / list_.size();
    double sum = 0;
    for (const std::shared_ptr<hittable> &o : list_) {
        sum += weight * o->pdf_value(origin, direction);
    }
    return sum;
}

inline vec hittable_list::random(const point &origin) const {
    return list_[random_int(0, list_.size() - 1)]->random(origin);
}

#endif  // HITTABLE_LIST_H_
