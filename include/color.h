#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>  // std::ostream

#include "util.h"  // color_cast
#include "vec.h"   // constructor color(const vec&)

struct color {
   public:
    color();
    color(double r, double g, double b);
    color(const vec &v);

    double r() const;
    double g() const;
    double b() const;

    color operator-() const;

    color operator+(const color &c) const;

    color operator-(const color &c) const;

    color operator*(double x) const;

    color operator/(double x) const;

    color &operator+=(const color &c);

    color &operator-=(const color &c);

    color &operator*=(double x);

    color &operator/=(double x);

   private:
    double r_, g_, b_;
};

color operator+(const color &c, const vec &v);
color operator+(const vec &v, const color &c);
color operator*(double x, const color &c);
std::ostream &operator<<(std::ostream &os, const color &c);

color mix(const color &a, const color &b, double alpha);
color sample_cast(const color &c, int samples);

inline color::color() : color{0.0, 0.0, 0.0} {}

inline color::color(double r, double g, double b) : r_(r), g_(g), b_(b) {}

inline color::color(const vec &v) : r_{v.x()}, g_{v.y()}, b_{v.z()} {}

inline double color::r() const { return r_; }

inline double color::g() const { return g_; }

inline double color::b() const { return b_; }

inline color color::operator-() const {
    return color{-r_, -g_, -b_};
}

inline color color::operator+(const color &c) const {
    return color{r_ + c.r_, g_ + c.g_, b_ + c.b_};
}

inline color color::operator-(const color &c) const {
    return color{r_ - c.r_, g_ - c.g_, b_ - c.b_};
}

inline color color::operator*(double x) const {
    return color{r_ * x, g_ * x, b_ * x};
}

inline color color::operator/(double x) const {
    return color{r_ / x, g_ / x, b_ / x};
}

inline color &color::operator+=(const color &c) {
    r_ += c.r_;
    g_ += c.g_;
    b_ += c.b_;
    return *this;
}

inline color &color::operator-=(const color &c) {
    r_ -= c.r_;
    g_ -= c.g_;
    b_ -= c.b_;
    return *this;
}

inline color &color::operator*=(double x) {
    r_ *= x;
    g_ *= x;
    b_ *= x;
    return *this;
}

inline color &color::operator/=(double x) {
    r_ /= x;
    g_ /= x;
    b_ /= x;
    return *this;
}

inline color operator+(const color &c, const vec &v) {
    return color{c.r() + v.x(), c.g() + v.y(), c.b() + v.z()};
}

inline color operator+(const vec &v, const color &c) {
    return c + v;
}

inline color operator*(double x, const color &c) {
    return c * x;
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
