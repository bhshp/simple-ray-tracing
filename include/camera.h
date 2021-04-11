#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"  // ray
#include "vec.h"  // vec

struct camera {
   public:
    camera() : origin_{0.0, 0.0, 0.0},
               horizontal_{viewport_width, 0.0, 0.0},
               vertical_{0.0, viewport_height, 0.0},
               lower_left_{origin_ - (0.5 * vertical_) - (0.5 * horizontal_) - vec{0, 0, focal_length}} {}

    ray get_ray(double u, double v) {
        return ray{origin_, lower_left_ + (u * vertical_) + (v * horizontal_) - origin_};
    }

    int width() const { return image_width; }
    int height() const { return image_height; }

   private:
    const int width_ratio = 16;
    const int height_ratio = 9;

    const double aspect_ratio = 1.0 * width_ratio / height_ratio;

    const int image_width = 1600;
    const int image_height = static_cast<int>(1.0 * image_width / aspect_ratio);

    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;

    point origin_;
    vec horizontal_;
    vec vertical_;
    point lower_left_;
};

#endif  // CAMERA_H_