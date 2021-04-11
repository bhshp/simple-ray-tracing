#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>  // std::ostream

#include "util.h"  // color_cast
#include "vec.h"   // constructor color(const vec&)

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

inline color operator+(const color &c, const vec &v) {
    return color{c.r() + v.x(), c.g() + v.y(), c.b() + v.z()};
}

inline color operator+(const vec &v, const color &c) {
    return c + v;
}

template <typename T>
inline color operator*(T val, const color &t) {
    return t * val;
}

inline std::ostream &operator<<(std::ostream &os, const color &c) {
    return os << color_cast(c.r()) << ' ' << color_cast(c.g()) << ' ' << color_cast(c.b());
}

inline color mix(const color &a, const color &b, double alpha) {
    return (1.0 - alpha) * a + alpha * b;
}

inline color sample_cast(const color &c, int samples) {
    return c / samples;
}

#endif  // COLOR_H_
