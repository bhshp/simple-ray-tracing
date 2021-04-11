#include "sphere.h"

#include <cmath>
#include <optional>

#include "hit_record.h"  // hit_record
#include "hittable.h"    // hittable
#include "ray.h"         // ray
#include "vec.h"         // point vec

inline sphere::sphere() {}

inline sphere::sphere(const point& center, double r) : center_(center), radius_(r) {}

inline sphere::~sphere() {}

inline point sphere::center() const { return center_; }

inline double sphere::radius() const { return radius_; }

inline std::optional<hit_record> sphere::hit(const ray& r, double t_min, double t_max) const {
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
