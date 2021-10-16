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

#endif  // CAMERA_H_
