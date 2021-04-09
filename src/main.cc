#include <cmath>
#include <fstream>
#include <iostream>

#include "color.h"
#include "config.h"
#include "ray.h"
#include "vec.h"

vec origin{0, 0, 0};
vec horizontal{viewport_width, 0, 0};
vec vertical{0, viewport_height, 0};
vec lower_left = origin - (horizontal * 0.5) - (vertical * 0.5) - vec{0, 0, focal_length};

using std::endl;
using std::floor;
using std::ofstream;

double hit_sphere(const point& center, double radius, const ray& r) {
    vec oc = r.origin() - center;
    double a = r.direction().length2();
    double half_b = oc * r.direction();
    double c = oc.length2() - sqr(radius);
    double discriminant = half_b * half_b - a * c;
    return discriminant < 0 ? -1.0 : (-half_b - sqrt(discriminant)) / a;
}

color ray_color(const ray& r) {
    double t = hit_sphere(point(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec N = (r.at(t) - vec(0, 0, -1)).unit();
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec unit_direction = r.direction().unit();
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    ofstream out(path);
    out << "P3\n"
        << image_width << ' ' << image_height << "\n255\n";
    for (int i = image_height - 1; i >= 0; i--) {
        for (int j = 0; j < image_width; j++) {
            double u = double(j) / (image_width - 1);
            double v = double(i) / (image_height - 1);
            ray r{origin, lower_left + u * horizontal + v * vertical - origin};
            color pixel = ray_color(r);
            out << color_cast(pixel) << '\n';
        }
    }
    return 0;
}
