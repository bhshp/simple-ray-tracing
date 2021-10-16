#pragma once

#ifndef MOVING_SPHERE_H_
#define MOVING_SPHERE_H_

#include <optional>

#include "hittable.h"
#include "material.h"
#include "vec.h"

struct moving_sphere : public hittable {
   public:
    moving_sphere();
    moving_sphere(const point &center_1,
                  const point center_2,
                  double start,
                  double end,
                  double r,
                  const std::shared_ptr<material> &m);
    virtual ~moving_sphere();

    point start() const;
    point end() const;
    point center(double time) const;
    double radius() const;

    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;

   private:
    point center_1_;
    point center_2_;
    double start_;
    double end_;
    double radius_;
    std::shared_ptr<material> mat_;
};

#endif  // MOVING_SPHERE_H_
