#include <fstream>   // std::ofstream
#include <iostream>  // std::endl
#include <memory>    // std::make_shared

#include "compact.h"

color ray_color(const ray& r, const hittable& world) {
    if (result_type rec = world.hit(r, 0, inf); rec.has_value()) {
        return 0.5 * (rec->normal() + color{1, 1, 1});
    }
    const color white = color{1.0, 1.0, 1.0};
    const color blue{0.5, 0.7, 1.0};
    return mix(white, blue, 0.5 * (r.direction().unit().y() + 1.0));
}

int main() {
    camera cam;

    const int width = cam.width();
    const int height = cam.height();
    const int samples = 100;

    std::ofstream out(path);
    out << "P3\n"
        << cam.width() << ' ' << cam.height() << "\n255\n";

    // World
    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 0, -1}, 0.5));       // sphere
    world.push_back(std::make_shared<sphere>(point{0, -100.5, -1}, 100));  // ground

    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            color pixel;
            for (int k = 0; k < samples; k++) {
                double u = (i + random_double()) / (height - 1);
                double v = (j + random_double()) / (width - 1);
                ray r = cam.get_ray(u, v);
                pixel += ray_color(r, world);
            }
            out << sample_cast(pixel, samples) << '\n';
        }
    }
    out.flush();
    out.close();
    return 0;
}
