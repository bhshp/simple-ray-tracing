#pragma once

#ifndef SPHERE_H_
#define SPHERE_H_

#include <optional>

#include "hit_record.h"  // hit_record
#include "hittable.h"    // hittable
#include "ray.h"         // ray
#include "util.h"        // sqr
#include "vec.h"         // point vec

struct sphere : public hittable {
   public:
    sphere() {}
    sphere(point center, double r) : center_(center), radius_(r) {}
    ~sphere() {}

    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const override;

    inline point center() const { return center_; }
    inline double radius() const { return radius_; }

   private:
    point center_;
    double radius_;
};

std::optional<hit_record> sphere::hit(const ray& r, double t_min, double t_max) const {
    vec oc = r.origin() - center();
    double a = r.direction().length2();
    double half_b = oc * r.direction();
    double c = oc.length2() - sqr(radius());
    double delta = sqr(half_b) - a * c;
    if (delta < 0) {
        return std::nullopt;
    }
    double sqrt_delta = std::sqrt(delta);
    double root = (-half_b - sqrt_delta) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrt_delta) / a;
        if (root < t_min || root > t_max) {
            return std::nullopt;
        }
    }
    point p = r.at(root);
    vec normal = (p - center()) / radius();
    bool front_face = (r.direction() * normal) < 0;
    if (!front_face) {
        normal = -normal;
    }
    return std::make_optional<hit_record>(root, p, normal, front_face);
}

#endif  // SPHERE_H_
