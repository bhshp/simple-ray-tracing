#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"  // ray
#include "vec.h"  // vec point

struct camera {
   public:
    camera(double aspect_ratio,
           point look_from = point{0, 0, 0},
           point look_at = point{0, 0, -1},
           vec view_up = vec{0, 0, 0},
           double vertical_field_of_view_degrees = 90.0,
           double focus_dist = 1.0,
           double aperture = 0,
           double start = 0,
           double end = 0);

    ray get_ray(double u, double v);

   private:
    double viewport_height_;
    double viewport_width_;
    vec w_;
    vec u_;
    vec v_;
    point origin_;
    vec vertical_;
    vec horizontal_;
    point lower_left_;
    double lens_radius_;
    double start_;
    double end_;
};

inline camera::camera(double aspect_ratio,
                      point look_from,
                      point look_at,
                      vec view_up,
                      double vertical_field_of_view_degrees,
                      double focus_dist,
                      double aperture,
                      double start,
                      double end)
    : viewport_height_{2.0 * std::tan(deg2rad(vertical_field_of_view_degrees) / 2)},
      viewport_width_{aspect_ratio * viewport_height_},
      w_{(look_from - look_at).unit()},
      u_{(view_up ^ w_).unit()},
      v_{w_ ^ u_},
      origin_{look_from},
      vertical_{focus_dist * viewport_height_ * v_},
      horizontal_{focus_dist * viewport_width_ * u_},
      lower_left_{origin_ - (vertical_ * 0.5) - (horizontal_ * 0.5) - focus_dist * w_},
      lens_radius_{aperture / 2},
      start_{start},
      end_{end} {}

inline ray camera::get_ray(double s, double t) {
    vec radius = lens_radius_ * random_in_unit_disk();
    vec offset = u_ * radius.x() + v_ * radius.y();
    return ray{origin_ + offset,
               lower_left_ + (s * vertical_) + (t * horizontal_) - origin_ - offset,
               random_double(start_, end_)};
}

#endif  // CAMERA_H_
