#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>  // std::ostream

#include "vec.h"

struct color {
   public:
    color(double r, double g, double b) : r_(r), g_(g), b_(b) {}
    color() : color{0.0, 0.0, 0.0} {}
    color(const vec &v) : r_{v.x()}, g_{v.y()}, b_{v.z()} {}

    double r() const { return r_; }
    double g() const { return g_; }
    double b() const { return b_; }

    color operator+(const color &c) const {
        return color{r_ + c.r_, g_ + c.g_, b_ + c.b_};
    }

    color operator-(const color &c) const {
        return color{r_ - c.r_, g_ - c.g_, b_ - c.b_};
    }

    color operator-() const {
        return color{-r_, -g_, -b_};
    }

    color operator*(double x) const {
        return color{r_ * x, g_ * x, b_ * x};
    }

    color operator/(double x) const {
        return color{r_ / x, g_ / x, b_ / x};
    }

    color &operator+=(const color &c) {
        r_ += c.r_;
        g_ += c.g_;
        b_ += c.b_;
        return *this;
    }

    color &operator-=(const color &c) {
        r_ -= c.r_;
        g_ -= c.g_;
        b_ -= c.b_;
        return *this;
    }

    color &operator*=(double x) {
        r_ *= x;
        g_ *= x;
        b_ *= x;
        return *this;
    }

    color &operator/=(double x) {
        r_ /= x;
        g_ /= x;
        b_ /= x;
        return *this;
    }

    template <typename T>
    color operator*(const T &val) const {
        return color{r_ * val, g_ * val, b_ * val};
    }

   private:
    double r_, g_, b_;
};

#endif  // COLOR_H_
