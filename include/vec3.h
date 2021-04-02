#pragma once

#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>        // std::sqrt
#include <iostream>     // std::ostream
#include <type_traits>  // std::enable_if_t std::is_floating_point_v

namespace {

double sqr(double x) {
    return x * x;
}

int color_cast(double color) {
    if (color <= 0) {
        return 0;
    } else if (color >= 1.0) {
        return 255;
    }
    return static_cast<int>(color * 256.0);
}

}  // namespace

struct vec3 {
    friend inline std::ostream &operator<<(std::ostream &os, const vec3 &color) {
        return os << color_cast(color.x()) << ' ' << color_cast(color.y()) << ' ' << color_cast(color.y()) << '\n';
    }

   public:
    vec3(double _x, double _y, double _z) : x_{_x}, y_{_y}, z_{_z} {}
    vec3() : vec3{0, 0, 0} {}
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
    double length_2() const {
        return sqr(x_) + sqr(y_) + sqr(z_);
    }
    double length() const {
        return std::sqrt(length_2());
    }
    vec3 unit() const {
        return *this / this->length();
    }
    double &operator[](size_t index) {
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
    vec3 operator+(const vec3 &v) const {
        return vec3{x_ + v.x_, y_ + v.y_, z_ + v.z_};
    }
    vec3 operator-(const vec3 &v) const {
        return vec3{x_ - v.x_, y_ - v.y_, z_ - v.z_};
    }
    vec3 operator-() const {
        return vec3{-x_, -y_, -z_};
    }
    vec3 operator^(const vec3 &v) const {
        return vec3{y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_};
    }
    double operator*(const vec3 &v) const {
        return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
    }
    vec3 &operator+=(const vec3 &v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
        return *this;
    }
    vec3 &operator-=(const vec3 &v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
        return *this;
    }

    template <typename Tp>
    vec3 operator*(const Tp &t) const {
        return vec3{x_ * t, y_ * t, z_ * t};
    }
    template <typename Tp>
    vec3 operator/(const Tp &t) const {
        return vec3{x_ / t, y_ / t, z_ / t};
    }
    template <typename Tp>
    vec3 &operator*=(const Tp &t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }
    template <typename Tp>
    vec3 &operator/=(const Tp &t) {
        x_ /= t;
        y_ /= t;
        z_ /= t;
        return *this;
    }

   private:
    double x_;
    double y_;
    double z_;
};

using point = vec3;
using color = vec3;

#endif  // VEC3_H_
