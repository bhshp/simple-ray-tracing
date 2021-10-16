#pragma once

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <memory>

#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec.h"

struct rectangle : public hittable {
   public:
    virtual ~rectangle();

    virtual bound_result_type bounding_box(double time_0, double time_1) const = 0;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const = 0;
};

struct xy_rectangle : public rectangle {
   public:
    xy_rectangle(double x0, double x1, double y0, double y1, double z, const std::shared_ptr<material> &p);
    virtual ~xy_rectangle();

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;

   private:
    double x0_, x1_, y0_, y1_, z_;
    std::shared_ptr<material> mat_;
};

struct xz_rectangle : public rectangle {
   public:
    xz_rectangle(double x0, double x1, double z0, double z1, double y, const std::shared_ptr<material> &p);
    virtual ~xz_rectangle();

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;
    virtual double pdf_value(const point &origin, const vec &direction) const override;
    virtual vec random(const point &origin) const override;

   private:
    double x0_, x1_, z0_, z1_, y_;
    std::shared_ptr<material> mat_;
};

struct yz_rectangle : public rectangle {
   public:
    yz_rectangle(double y0, double y1, double z0, double z1, double x, const std::shared_ptr<material> &p);
    virtual ~yz_rectangle();

    virtual bound_result_type bounding_box(double time_0, double time_1) const override;
    virtual hit_result_type hit(const ray &r, double t_min, double t_max) const override;

   private:
    double y0_, y1_, z0_, z1_, x_;
    std::shared_ptr<material> mat_;
};

#endif  // RECTANGLE_H_