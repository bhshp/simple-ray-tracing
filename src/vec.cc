#include "vec.h"

vec::vec(double _x, double _y, double _z) : x_{_x}, y_{_y}, z_{_z} {}

vec::vec() : vec{0, 0, 0} {}

bool vec::near_zero() const {
    return std::fabs(x()) < eps && std::fabs(y()) < eps && std::fabs(z()) < eps;
}

double vec::x() const { return x_; }

double vec::y() const { return y_; }

double vec::z() const { return z_; }

double vec::length2() const {
    return sqr(x_) + sqr(y_) + sqr(z_);
}

double vec::length() const {
    return std::sqrt(length2());
}

vec vec::unit() const {
    return *this / length();
}

vec vec::operator-() const {
    return vec{-x_, -y_, -z_};
}

vec vec::operator+(const vec &v) const {
    return vec{x_ + v.x_, y_ + v.y_, z_ + v.z_};
}

vec vec::operator-(const vec &v) const {
    return vec{x_ - v.x_, y_ - v.y_, z_ - v.z_};
}

vec vec::operator^(const vec &v) const {
    return vec{y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_};
}

vec vec::operator*(double x) const {
    return vec{x_ * x, y_ * x, z_ * x};
}

vec vec::operator/(double x) const {
    return vec{x_ / x, y_ / x, z_ / x};
}

double vec::operator*(const vec &v) const {
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

double vec::operator[](size_t index) const {
    switch (index) {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw "now such element";
    }
}

double &vec::operator[](size_t index) {
    switch (index) {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw "now such element";
    }
}

vec &vec::operator+=(const vec &v) {
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
}

vec &vec::operator-=(const vec &v) {
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
}

vec &vec::operator*=(double x) {
    x_ *= x;
    y_ *= x;
    z_ *= x;
    return *this;
}

vec &vec::operator/=(double x) {
    x_ /= x;
    y_ /= x;
    z_ /= x;
    return *this;
}

vec &vec::unitize() {
    double len = length();
    this->x_ /= len;
    this->y_ /= len;
    this->z_ /= len;
    return *this;
}

vec vec::random() {
    return vec{random_double(), random_double(), random_double()};
}

vec vec::random(double min, double max) {
    return vec{random_double(min, max), random_double(min, max), random_double(min, max)};
}

vec operator*(double val, const vec &t) {
    return t * val;
}

std::ostream &operator<<(std::ostream &os, const vec &v) {
    return os << v.x() << ' ' << v.y() << ' ' << v.z();
}

vec random_in_unit_sphere() {
    do {
        vec p = vec::random(-1, 1);
        if (p.length2() < 1) {
            return p;
        }
    } while (true);
}

vec random_in_hemisphere(const vec &normal) {
    vec in_unit_sphere = random_in_unit_sphere();
    return normal * in_unit_sphere > 0 ? in_unit_sphere : -in_unit_sphere;
}

vec random_in_unit_disk() {
    do {
        vec p{random_double(-1, 1), random_double(-1, 1), 0};
        if (p.length2() < 1) {
            return p;
        }
    } while (true);
}

vec random_unit_vector() {
    return random_in_unit_sphere().unit();
}

vec random_cosine_direction() {
    const double phi = 2 * pi * random_double();
    double r = random_double();
    double x = std::cos(phi) * std::sqrt(r);
    double y = std::sin(phi) * std::sqrt(r);
    double z = std::sqrt(1 - r);
    return vec{x, y, z};
}

vec random_to_sphere(double radius, double length2) {
    const double phi = 2 * pi * random_double();
    double r = random_double();
    double z = 1 + r * (std::sqrt(1 - sqr(radius) / length2) - 1);
    double x = std::cos(phi) * std::sqrt(1 - sqr(z));
    double y = std::sin(phi) * std::sqrt(1 - sqr(z));
    return vec{x, y, z};
}

vec reflect(const vec &v, const vec &n) {
    return v - (2 * v * n) * n;
}

vec refract(const vec &uv, const vec &n, double ratio) {
    double cos_theta = std::min(-uv * n, 1.0);
    vec r_vertical = ratio * (uv + cos_theta * n);
    vec r_parallel = -std::sqrt(1 - r_vertical.length2()) * n;
    return r_vertical + r_parallel;
}
