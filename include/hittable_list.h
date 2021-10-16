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

#endif  // HITTABLE_LIST_H_
