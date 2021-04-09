#pragma once

#ifndef vec_H_
#define vec_H_

#include <cmath>     // std::sqrt
#include <iostream>  // std::ostream

#include "util.h"

struct vec {
   public:
    vec(double _x, double _y, double _z) : x_{_x}, y_{_y}, z_{_z} {}
    vec() : vec{0, 0, 0} {}
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
    double length2() const {
        return sqr(x_) + sqr(y_) + sqr(z_);
    }
    double length() const {
        return std::sqrt(length2());
    }
    vec unit() const {
        return *this / length();
    }
    vec &unitize() {
        double len = length();
        this->x_ /= len;
        this->y_ /= len;
        this->z_ /= len;
        return *this;
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
    vec operator+(const vec &v) const {
        return vec{x_ + v.x_, y_ + v.y_, z_ + v.z_};
    }
    vec operator-(const vec &v) const {
        return vec{x_ - v.x_, y_ - v.y_, z_ - v.z_};
    }
    vec operator-() const {
        return vec{-x_, -y_, -z_};
    }
    vec operator^(const vec &v) const {
        return vec{y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_};
    }
    double operator*(const vec &v) const {
        return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
    }
    vec &operator+=(const vec &v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
        return *this;
    }
    vec &operator-=(const vec &v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
        return *this;
    }

    template <typename Tp>
    vec operator*(const Tp &t) const {
        return vec{x_ * t, y_ * t, z_ * t};
    }
    template <typename Tp>
    vec operator/(const Tp &t) const {
        return vec{x_ / t, y_ / t, z_ / t};
    }
    template <typename Tp>
    vec &operator*=(const Tp &t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }
    template <typename Tp>
    vec &operator/=(const Tp &t) {
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

template <typename T>
vec operator*(T val, const vec &t) {
    return vec{val * t.x(), val * t.y(), val * t.z()};
}

using point = vec;
using color = vec;

#endif  // vec_H_
