#include "ortho.h"

ortho::ortho() {}

ortho::ortho(const vec& v) : w_{v.unit()},
                             v_{(w_ ^ (std::fabs(w_.x()) > 0.9 ? vec{0, 1, 0} : vec{1, 0, 0})).unit()},
                             u_{w_ ^ v_} {}

const vec& ortho::operator[](size_t index) const {
    if (index >= 3) {
        throw "No Such Element";
    } else if (index == 0) {
        return u_;
    } else if (index == 1) {
        return v_;
    }
    return w_;
}

vec ortho::u() const { return u_; }

vec ortho::v() const { return v_; }

vec ortho::w() const { return w_; }

vec ortho::local(double a, double b, double c) const {
    return a * u_ + b * v_ + c * w_;
}

vec ortho::local(const vec& v) const {
    return local(v.x(), v.y(), v.z());
}
