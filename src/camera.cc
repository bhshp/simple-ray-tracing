#include "camera.h"

inline camera::camera() : origin_{0.0, 0.0, 0.0},
                   horizontal_{viewport_width, 0.0, 0.0},
                   vertical_{0.0, viewport_height, 0.0},
                   lower_left_{origin_ - (0.5 * vertical_) - (0.5 * horizontal_) - vec{0, 0, focal_length}} {}

inline ray camera::get_ray(double u, double v) {
    return ray{origin_, lower_left_ + (u * vertical_) + (v * horizontal_) - origin_};
}

inline int camera::width() const { return image_width; }

inline int camera::height() const { return image_height; }
