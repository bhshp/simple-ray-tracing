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
    ~hittable_list();

    void push_back(const std::shared_ptr<hittable> &object);
    void pop_back();
    void push_front(const std::shared_ptr<hittable> &object);
    void pop_front();
    void clear();

    virtual std::optional<hit_record> hit(const ray &r, double t_min, double t_max) const override;

   private:
    std::list<std::shared_ptr<hittable>> list_;
};

#endif  // HITTABLE_LIST_H_
