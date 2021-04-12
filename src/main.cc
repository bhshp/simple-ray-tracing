#include <fstream>   // std::ofstream
#include <iostream>  // std::endl
#include <memory>    // std::make_shared
#include <string>    // std::string

#include "compact.h"
#include "progress_bar.h"

inline color ray_color(const ray& r, const hittable& world, int depth) {
    if (depth <= 0) {
        return color{};
    }
    if (hit_result_type rec = world.hit(r, eps, inf); rec.has_value()) {
        if (scatter_result_type scatter = rec->mat()->scatter(r, rec.value()); scatter.has_value()) {
            return scatter->first % ray_color(scatter->second, world, depth - 1);
        }
        return color{};
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
    const int max_depth = 100;

    std::ofstream out(path);
    out << "P3\n"
        << cam.width() << ' ' << cam.height() << "\n255\n";

    // Materials
    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.0});
    std::shared_ptr<dielectric> material_center = std::make_shared<dielectric>(1.5);
    std::shared_ptr<dielectric> material_left = std::make_shared<dielectric>(1.5);
    std::shared_ptr<metal> material_right = std::make_shared<metal>(color{0.8, 0.6, 0.2}, 1.0);

    // World
    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, -100.5, -1}, 100, material_ground));
    world.push_back(std::make_shared<sphere>(point{0, 0, -1}, 0.5, material_center));
    world.push_back(std::make_shared<sphere>(point{-1, 0, -1}, 0.5, material_left));
    world.push_back(std::make_shared<sphere>(point{1, 0, -1}, 0.5, material_right));

    progress_bar bar{std::cerr, height};

    for (int i = height - 1; i >= 0; i--) {
        bar.output(i);
        for (int j = 0; j < width; j++) {
            color pixel;
            for (int k = 0; k < samples; k++) {
                double u = (i + random_double()) / (height - 1);
                double v = (j + random_double()) / (width - 1);
                ray r = cam.get_ray(u, v);
                pixel += ray_color(r, world, max_depth);
            }
            out << sample_cast(pixel, samples) << '\n';
        }
    }
    bar.complete();
    out.flush();
    out.close();
    return 0;
}
