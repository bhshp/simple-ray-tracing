#pragma once

#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>
#include <memory>
#include <optional>

#include "hit_record.h"
#include "hittable.h"
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

// Implementation

inline sphere::sphere() {}

inline sphere::sphere(const point& center,
                      double r,
                      const std::shared_ptr<material>& mat) : center_{center},
                                                              radius_{r},
                                                              mat_{mat} {}

inline sphere::~sphere() {}

inline point sphere::center() const { return center_; }

inline double sphere::radius() const { return radius_; }

inline std::shared_ptr<material> sphere::mat() const { return mat_; }

inline bound_result_type sphere::bounding_box(double, double) const {
    double r = radius();
    vec c = center();
    vec rad_vec{r, r, r};
    return std::make_optional<aabb>(c - rad_vec, c + rad_vec);
}

inline hit_result_type sphere::hit(const ray& r, double t_min, double t_max) const {
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
    std::pair<double, double> uv = get_sphere_uv(normal);
    return std::make_optional<hit_record>(root, p, normal, front_face, mat(), uv.first, uv.second);
}

inline double sphere::pdf_value(const point& origin, const vec& direction) const {
    if (hit_result_type rec = this->hit(ray{origin, direction}, eps, inf); rec.has_value()) {
        double cos_theta_max  = std::sqrt(1 - sqr(radius_) / (center_ - origin).length2());
        double solid_angle = 2 * pi * (1 - cos_theta_max);
        return 1.0 / solid_angle;
    }
    return 0;
}

inline vec sphere::random(const point& origin) const {
    vec direction = center_ - origin;
    double length2 = direction.length2();
    return ortho{direction}.local(random_to_sphere(radius_, length2));
}

inline std::pair<double, double> get_sphere_uv(const point& p) {
    double theta = std::acos(-p.y());
    double phi = std::atan2(-p.z(), p.x()) + pi;
    return {phi / (2 * pi), theta / pi};
}

#endif  // SPHERE_H_
