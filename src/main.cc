#include <fstream>   // std::ofstream
#include <iostream>  // std::endl
#include <memory>    // std::make_shared
#include <string>    // std::string

#include "compact.h"
#include "generator.h"
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
    static const color white = color{1.0, 1.0, 1.0};
    static const color blue{0.5, 0.7, 1.0};
    return mix(white, blue, 0.5 * (r.direction().unit().y() + 1.0));
}

int main() {
    canvas cvs{image_width, image_height};
    double aspect_ratio = cvs.aspect_ratio();

    point look_from = point{13, 2, 3};
    point look_at = point{0, 0, 0};
    vec view_up = vec{0, 1, 0};
    double vertical_field_of_view_degrees = 20;
    double focus_dist = 10;
    double aperture = 0.1;
    double start_time = 0.0;
    double end_time = 0.0;            

    hittable_list world;

    switch (0) {
        case 1:
            std::cout << "Random World" << std::endl;
            aperture = 0.1;
            start_time = 0.0;
            end_time = 1.0;
            world = random_world();
            break;
        case 2:
            std::cout << "Two Spheres" << std::endl;
            world = two_spheres();
            break;
        case 3:
            std::cout << "Two Perlin Spheres" << std::endl;
            world = two_perlin_spheres();
            break;
        default:
        case 4:
            std::cout << "Earth" << std::endl;
            world = earth();
            break;
    }

    camera cam{aspect_ratio, look_from, look_at, view_up, vertical_field_of_view_degrees, focus_dist, aperture, start_time, end_time};

    {
        std::ofstream out(path);
        out << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";
        progress_bar bar{std::cerr, image_height};
        for (int i = image_height - 1; i >= 0; i--, bar++) {
            for (int j = 0; j < image_width; j++) {
                color pixel;
                for (int k = 0; k < samples; k++) {
                    double u = (i + random_double()) / (image_height - 1);
                    double v = (j + random_double()) / (image_width - 1);
                    ray r = cam.get_ray(u, v);
                    pixel += ray_color(r, world, max_depth);
                }
                out << sample_cast(pixel, samples) << '\n';
            }
        }
        out.close();
    }
    return 0;
}
