#include "sphere.h"

sphere::sphere() {}

sphere::sphere(const point& center,
               double r,
               const std::shared_ptr<material>& mat) : center_{center},
                                                       radius_{r},
                                                       mat_{mat} {}

sphere::~sphere() {}

point sphere::center() const { return center_; }

double sphere::radius() const { return radius_; }

std::shared_ptr<material> sphere::mat() const { return mat_; }

bound_result_type sphere::bounding_box(double, double) const {
    double r = radius();
    vec c = center();
    vec rad_vec{r, r, r};
    return std::make_optional<aabb>(c - rad_vec, c + rad_vec);
}

hit_result_type sphere::hit(const ray& r, double t_min, double t_max) const {
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

double sphere::pdf_value(const point& origin, const vec& direction) const {
    if (hit_result_type rec = this->hit(ray{origin, direction}, eps, inf); rec.has_value()) {
        double cos_theta_max = std::sqrt(1 - sqr(radius_) / (center_ - origin).length2());
        double solid_angle = 2 * pi * (1 - cos_theta_max);
        return 1.0 / solid_angle;
    }
    return 0;
}

vec sphere::random(const point& origin) const {
    vec direction = center_ - origin;
    double length2 = direction.length2();
    return ortho{direction}.local(random_to_sphere(radius_, length2));
}

std::pair<double, double> get_sphere_uv(const point& p) {
    double theta = std::acos(-p.y());
    double phi = std::atan2(-p.z(), p.x()) + pi;
    return {phi / (2 * pi), theta / pi};
}
