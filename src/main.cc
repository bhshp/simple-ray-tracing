#include <cmath>     // std::sqrt
#include <fstream>   // std::ofstream
#include <iostream>  // std::endl

#include "common.h"

color ray_color(const ray& r, const hittable& world) {
    if (result_type rec = world.hit(r, 0, inf); rec.has_value()) {
        return 0.5 * (rec->normal() + color{1, 1, 1});
    }
    const color white = color{1.0, 1.0, 1.0};
    const color blue{0.5, 0.7, 1.0};
    return mix(white, blue, 0.5 * (r.direction().unit().y() + 1.0));
}

int main() {
    std::ofstream out(path);
    out << "P3\n"
        << image_width << ' ' << image_height << "\n255\n";

    // World
    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 0, -1}, 0.5));       // sphere
    world.push_back(std::make_shared<sphere>(point{0, -100.5, -1}, 100));  // ground

    for (int i = image_height - 1; i >= 0; i--) {
        for (int j = 0; j < image_width; j++) {
            double u = double(j) / (image_width - 1),
                   v = double(i) / (image_height - 1);
            out << ray_color(ray{origin, lower_left + u * horizontal + v * vertical - origin}, world) << '\n';
        }
    }
    return 0;
}
