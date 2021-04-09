#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>

#include "vec.h"

int color_cast(double color) {
    if (color <= 0) {
        return 0;
    } else if (color >= 1.0) {
        return 255;
    }
    return static_cast<int>(color * 256.0);
}

namespace impl {
struct color_cast_impl {
   public:
    color_cast_impl(const vec &v) : v_(v) {}
    double x() const { return v_.x(); }
    double y() const { return v_.y(); }
    double z() const { return v_.z(); }

   private:
    const vec &v_;
};
}  // namespace impl

impl::color_cast_impl color_cast(const vec &color) {
    return impl::color_cast_impl{color};
}

inline std::ostream &operator<<(std::ostream &os, const vec &color) {
    return os << color.x() << ' ' << color.y() << ' ' << color.z();
}

inline std::ostream &operator<<(std::ostream &os, const impl::color_cast_impl &color) {
    return os << color_cast(color.x()) << ' ' << color_cast(color.y()) << ' ' << color_cast(color.z());
}

#endif  // COLOR_H_
