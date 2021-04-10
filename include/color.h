#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>  // std::ostream

#include "vec.h"

inline int color_cast(double c) {
    if (c <= 0) {
        return 0;
    } else if (c >= 1.0) {
        return 255;
    }
    return static_cast<int>(c * 256.0);
}

struct color {
   public:
    friend inline std::ostream &operator<<(std::ostream &os, const color &c) {
        return os << color_cast(c.r_) << ' ' << color_cast(c.g_) << ' ' << color_cast(c.b_);
    }

    color(double r, double g, double b) : r_(r), g_(g), b_(b) {}
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

    template <typename T>
    color operator*(const T &val) const {
        return color{r_ * val, g_ * val, b_ * val};
    }

   private:
    double r_, g_, b_;
};

#endif  // COLOR_H_
