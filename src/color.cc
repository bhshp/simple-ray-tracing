#include "color.h"

color::color() : color{0.0, 0.0, 0.0} {}

color::color(double r, double g, double b) : r_(r), g_(g), b_(b) {}

color::color(const vec &v) : r_{v.x()}, g_{v.y()}, b_{v.z()} {}

double color::r() const { return r_; }

double color::g() const { return g_; }

double color::b() const { return b_; }

color color::operator-() const {
    return color{-r_, -g_, -b_};
}

color color::operator+(const color &c) const {
    return color{r_ + c.r_, g_ + c.g_, b_ + c.b_};
}

color color::operator-(const color &c) const {
    return color{r_ - c.r_, g_ - c.g_, b_ - c.b_};
}

color color::operator*(double x) const {
    return color{r_ * x, g_ * x, b_ * x};
}

color color::operator/(double x) const {
    return color{r_ / x, g_ / x, b_ / x};
}

color color::operator%(const color &c) const {
    return color{r_ * c.r_, g_ * c.g_, b_ * c.b_};
}

color &color::operator+=(const color &c) {
    r_ += c.r_;
    g_ += c.g_;
    b_ += c.b_;
    return *this;
}

color &color::operator-=(const color &c) {
    r_ -= c.r_;
    g_ -= c.g_;
    b_ -= c.b_;
    return *this;
}

color &color::operator*=(double x) {
    r_ *= x;
    g_ *= x;
    b_ *= x;
    return *this;
}

color &color::operator/=(double x) {
    r_ /= x;
    g_ /= x;
    b_ /= x;
    return *this;
}

color operator+(const color &c, const vec &v) {
    return color{c.r() + v.x(), c.g() + v.y(), c.b() + v.z()};
}

color operator+(const vec &v, const color &c) {
    return c + v;
}

color operator*(double x, const color &c) {
    return c * x;
}

std::ostream &operator<<(std::ostream &os, const color &c) {
    return os << color_cast(c.r()) << ' ' << color_cast(c.g()) << ' ' << color_cast(c.b());
}

color mix(const color &a, const color &b, double alpha) {
    return (1.0 - alpha) * a + alpha * b;
}

color sample_cast(const color &c, int samples) {
    return color{std::sqrt(c.r() / samples),
                 std::sqrt(c.g() / samples),
                 std::sqrt(c.b() / samples)};
}

color random_color() {
    return random_color(0.0, 1.0);
}

color random_color(double min, double max) {
    return color{random_double(min, max), random_double(min, max), random_double(min, max)};
}
