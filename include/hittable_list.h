#pragma once

#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include <list>    // std::list
#include <memory>  // std::shared_ptr

#include "hit_record.h"  // hit_record
#include "hittable.h"    // hittable

struct hittable_list : public hittable {
   public:
    hittable_list();
    virtual ~hittable_list();

    void push_back(const std::shared_ptr<hittable> &object);
    void pop_back();
    void push_front(const std::shared_ptr<hittable> &object);
    void pop_front();
    void clear();

    virtual std::optional<hit_record> hit(const ray &r, double t_min, double t_max) const override;

   private:
    std::list<std::shared_ptr<hittable>> list_;
};

inline hittable_list::hittable_list() {}

inline hittable_list::~hittable_list() {}

inline void hittable_list::push_back(const std::shared_ptr<hittable> &object) {
    list_.push_back(object);
}

inline void hittable_list::pop_back() {
    list_.pop_back();
}

inline void hittable_list::push_front(const std::shared_ptr<hittable> &object) {
    list_.push_front(object);
}

inline void hittable_list::pop_front() {
    list_.pop_front();
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

#endif  // HITTABLE_LIST_H_
