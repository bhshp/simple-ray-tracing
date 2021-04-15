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

inline moving_sphere::moving_sphere() {}

inline moving_sphere::moving_sphere(const point &center_1,
                                    const point center_2,
                                    double start,
                                    double end,
                                    double r,
                                    const std::shared_ptr<material> &m) : center_1_{center_1},
                                                                          center_2_{center_2},
                                                                          start_{start},
                                                                          end_{end},
                                                                          radius_{r},
                                                                          mat_{m} {}

inline moving_sphere::~moving_sphere() {}

inline point moving_sphere::start() const {
    return center_1_;
}

inline point moving_sphere::end() const {
    return center_2_;
}

inline double moving_sphere::radius() const {
    return radius_;
}

inline point moving_sphere::center(double time) const {
    return center_1_ + (time - start_) / (end_ - start_) * (center_2_ - center_1_);
}

inline hit_result_type moving_sphere::hit(const ray &r, double t_min, double t_max) const {
    vec oc = r.origin() - center(r.time());
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
    vec normal = (p - center(r.time())) / radius();
    bool front_face = (r.direction() * normal) < 0;
    if (!front_face) {
        normal = -normal;
    }
    return std::make_optional<hit_record>(root, p, normal, front_face, mat_);
}

bound_result_type moving_sphere::bounding_box(double time_0, double time_1) const {
    point first = center(time_0);
    point second = center(time_1);
    double r = radius();
    vec rad_vec = vec{r, r, r};
    return std::make_optional<aabb>(surrounding_box(aabb{first - rad_vec,
                                                         first + rad_vec},
                                                    aabb{second - rad_vec,
                                                         second + rad_vec}));
}

#endif  // MOVING_SPHERE_H_
