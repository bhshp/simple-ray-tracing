#include <cmath>
#include <fstream>
#include <iostream>

#include "ray.h"
#include "vec3.h"

const int width_ratio = 16;
const int height_ratio = 9;
const double aspect_ratio = 1.0 * width_ratio / height_ratio;

const int image_width = 400;
const int image_height = static_cast<int>(1.0 * image_width / aspect_ratio);

double viewport_height = 2.0;
double viewport_width = aspect_ratio * viewport_height;
double focal_length = 1.0;

vec3 origin{0, 0, 0};
vec3 horizontal{viewport_width, 0, 0};
vec3 vertical{0, viewport_height, 0};
vec3 lower_left = origin - horizontal / 2 - vertical / 2 - vec3{0, 0, focal_length};

using std::endl;
using std::floor;
using std::ofstream;

color ray_color(const ray& r) {
    vec3 unit = r.direction().unit();
    double t = 0.5 * (unit.y() + 1);
    return (1.0 - t) * color{1.0, 1.0, 1.0} +
           t * color{0.5, 0.7, 1.0};
}

int main(int argc, char** argv) {
    ofstream out("out.ppm");
    out << "P3\n"
        << image_width << ' ' << image_height << "\n255\n";
    for (int i = image_height - 1; i >= 0; i--) {
        for (int j = 0; j < image_width; j++) {
            double u = 1.0;  //double(j) / (image_width - 1);
            double v = 1.0;  //double(i) / (image_height - 1);
            ray r{origin, lower_left + u * horizontal + v * vertical - origin};
            color pixel = ray_color(r);
            out << pixel << std::endl;
        }
    }
    return 0;
}