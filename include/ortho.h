#pragma once

#ifndef ORTHO_H_
#define ORTHO_H_

#include "vec.h"

struct ortho {
   public:
    ortho();
    ortho(const vec& v);

    const vec& operator[](size_t index) const;

    vec u() const;
    vec v() const;
    vec w() const;

    vec local(double a, double b, double c) const;
    vec local(const vec& v) const;

   private:
    vec w_, v_, u_;
};

inline ortho::ortho() {}

inline ortho::ortho(const vec& v) : w_{v.unit()},
                                    v_{(w_ ^ (std::fabs(w_.x()) > 0.9 ? vec{0, 1, 0} : vec{1, 0, 0})).unit()},
                                    u_{w_ ^ v_} {}

inline const vec& ortho::operator[](size_t index) const {
    if (index >= 3) {
        throw "No Such Element";
    } else if (index == 0) {
        return u_;
    } else if (index == 1) {
        return v_;
    }
    return w_;
}

inline vec ortho::u() const { return u_; }

inline vec ortho::v() const { return v_; }

inline vec ortho::w() const { return w_; }

inline vec ortho::local(double a, double b, double c) const {
    return a * u_ + b * v_ + c * w_;
}

inline vec ortho::local(const vec& v) const {
    return local(v.x(), v.y(), v.z());
}

#endif  // ORTHO_H_
