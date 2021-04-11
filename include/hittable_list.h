#pragma once

#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include <memory>  // std::shared_ptr
#include <vector>  // std::vector

#include "hittable.h"

struct hittable_list : public hittable {
   public:
    hittable_list();
    ~hittable_list();
    void clear();
    void push_back(const std::shared_ptr<hittable> &object);
    virtual std::optional<hit_record> hit(const ray &r, double t_min, double t_max) const override;

   private:
    std::vector<std::shared_ptr<hittable>> list_;
};

hittable_list::hittable_list() {}

hittable_list::~hittable_list() {}

void hittable_list::clear() {
    list_.clear();
}

void hittable_list::push_back(const std::shared_ptr<hittable> &object) {
    list_.push_back(object);
}

std::optional<hit_record> hittable_list::hit(const ray &r, double t_min, double t_max) const {
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

#endif