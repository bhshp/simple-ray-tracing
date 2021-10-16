#include "rectangle.h"

// Implementation

rectangle::~rectangle() {}

xy_rectangle::xy_rectangle(double x0,
                           double x1,
                           double y0,
                           double y1,
                           double z,
                           const std::shared_ptr<material> &p) : x0_{x0},
                                                                 x1_{x1},
                                                                 y0_{y0},
                                                                 y1_{y1},
                                                                 z_{z},
                                                                 mat_{p} {}

xy_rectangle::~xy_rectangle() {}

bound_result_type xy_rectangle::bounding_box(double, double) const {
    return std::make_optional<aabb>(point{x0_, y0_, z_ - eps}, point{x1_, y1_, z_ + eps});
}

hit_result_type xy_rectangle::hit(const ray &r, double t_min, double t_max) const {
    double t = (z_ - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max) {
        return std::nullopt;
    }
    point p = r.at(t);
    double x = p.x(), y = p.y();
    if (x < x0_ || x > x1_ || y < y0_ || y > y1_) {
        return std::nullopt;
    }
    double u = (x - x0_) / (x1_ - x0_);
    double v = (y - y0_) / (y1_ - y0_);
    vec normal{0, 0, 1};
    bool front_face = (r.direction() * normal) < 0;
    if (!front_face) {
        normal = -normal;
    }
    return std::make_optional<hit_record>(t, p, normal, front_face, mat_, u, v);
}

xz_rectangle::xz_rectangle(double x0,
                           double x1,
                           double z0,
                           double z1,
                           double y,
                           const std::shared_ptr<material> &p) : x0_{x0},
                                                                 x1_{x1},
                                                                 z0_{z0},
                                                                 z1_{z1},
                                                                 y_{y},
                                                                 mat_{p} {}

xz_rectangle::~xz_rectangle() {}

bound_result_type xz_rectangle::bounding_box(double, double) const {
    return std::make_optional<aabb>(point{x0_, y_ - eps, z0_}, point{x1_, y_ + eps, z1_});
}

hit_result_type xz_rectangle::hit(const ray &r, double t_min, double t_max) const {
    double t = (y_ - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max) {
        return std::nullopt;
    }
    point p = r.at(t);
    double x = p.x(), z = p.z();
    if (x < x0_ || x > x1_ || z < z0_ || z > z1_) {
        return std::nullopt;
    }
    double u = (x - x0_) / (x1_ - x0_);
    double v = (z - z0_) / (z1_ - z0_);
    vec normal{0, 1, 0};
    bool front_face = (r.direction() * normal) < 0;
    if (!front_face) {
        normal = -normal;
    }
    return std::make_optional<hit_record>(t, p, normal, front_face, mat_, u, v);
}

double xz_rectangle::pdf_value(const point &origin, const vec &direction) const {
    if (hit_result_type rec = hit(ray{origin, direction}, eps, inf); rec.has_value()) {
        double area = (x1_ - x0_) * (z1_ - z0_);
        double length2 = sqr(rec->t()) * direction.length2();
        double cosine = std::fabs(direction * rec->normal() / direction.length());
        return length2 / (cosine * area);
    }
    return 0;
}

vec xz_rectangle::random(const point &origin) const {
    return point{random_double(x0_, x1_), y_, random_double(z0_, z1_)} - origin;
}

yz_rectangle::yz_rectangle(double y0,
                           double y1,
                           double z0,
                           double z1,
                           double x,
                           const std::shared_ptr<material> &p) : y0_{y0},
                                                                 y1_{y1},
                                                                 z0_{z0},
                                                                 z1_{z1},
                                                                 x_{x},
                                                                 mat_{p} {}

yz_rectangle::~yz_rectangle() {}

bound_result_type yz_rectangle::bounding_box(double, double) const {
    return std::make_optional<aabb>(point{x_ - eps, y0_, z0_}, point{x_ + eps, y1_, z1_});
}

hit_result_type yz_rectangle::hit(const ray &r, double t_min, double t_max) const {
    double t = (x_ - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max) {
        return std::nullopt;
    }
    point p = r.at(t);
    double y = p.y(), z = p.z();
    if (y < y0_ || y > y1_ || z < z0_ || z > z1_) {
        return std::nullopt;
    }
    double u = (y - y0_) / (y1_ - y0_);
    double v = (z - z0_) / (z1_ - z0_);
    vec normal{1, 0, 0};
    bool front_face = (r.direction() * normal) < 0;
    if (!front_face) {
        normal = -normal;
    }
    return std::make_optional<hit_record>(t, p, normal, front_face, mat_, u, v);
}
