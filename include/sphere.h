#pragma once

#ifndef SPHERE_H_
#define SPHERE_H_

#include <optional>

#include "hit_record.h"
#include "hittable.h"
#include "ray.h"
#include "vec.h"

struct sphere : public hittable {
   public:
    sphere();
    sphere(const point& center, double r);
    ~sphere();

    point center() const;
    double radius() const;

    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const override;

   private:
    point center_;
    double radius_;
};

#endif  // SPHERE_H_
