#include "camera.h"

camera::camera(double aspect_ratio,
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

ray camera::get_ray(double s, double t) {
    vec radius = lens_radius_ * random_in_unit_disk();
    vec offset = u_ * radius.x() + v_ * radius.y();
    return ray{origin_ + offset,
               lower_left_ + (s * vertical_) + (t * horizontal_) - origin_ - offset,
               random_double(start_, end_)};
}
