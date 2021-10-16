#pragma once

#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>
#include <memory>
#include <optional>

#include "hit_record.h"
#include "hittable.h"
#include "ortho.h"
#include "ray.h"
#include "vec.h"

struct sphere : public hittable {
   public:
    sphere();
    sphere(const point& center, double r, const std::shared_ptr<material>& m = nullptr);
    ~sphere();

    point center() const;
    double radius() const;
    std::shared_ptr<material> mat() const;

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray& r, double t_min, double t_max) const override;
    virtual double pdf_value(const point& origin, const vec& direction) const override;
    virtual vec random(const point& origin) const override;

   private:
    point center_;
    double radius_;
    std::shared_ptr<material> mat_;
};

std::pair<double, double> get_sphere_uv(const point& p);

#endif  // SPHERE_H_
