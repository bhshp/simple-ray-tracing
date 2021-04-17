#include <fstream>
#include <iostream>
#include <memory>

#include "compact.h"
#include "generator.h"
#include "progress_bar.h"

inline color ray_color(const ray& r, const color& background, const hittable& world,
                       const std::shared_ptr<hittable>& lights, int depth) {
    if (depth <= 0) {
        return color{};
    }
    if (hit_result_type rec = world.hit(r, eps, inf);
        rec.has_value()) {
        color emitted = rec->mat()->emit(r, rec.value(), rec->u(), rec->v(), rec->p());
        if (scatter_result_type scatter = rec->mat()->scatter(r, rec.value());
            scatter.has_value()) {
            std::shared_ptr<hittable_pdf> p0 = std::make_shared<hittable_pdf>(lights, rec->p());
            std::shared_ptr<cosine_pdf> p1 = std::make_shared<cosine_pdf>(rec->normal());
            mixture_pdf p{p0, p1};
            ray scattered{rec->p(), p.generate(), r.time()};
            double pdf_value = p.value(scattered.direction());
            return emitted + rec->mat()->pdf(r, rec.value(), scattered) *
                                 scatter->albedo() % ray_color(scattered, background, world, lights, depth - 1) /
                                 pdf_value;
        }
        return emitted;
    }
    return background;
}

int main() {
    const char* const path = "./target/out.ppm";

    const int image_width = 500;
    const int image_height = 500;

    const double aspect_ratio = 1.0 * image_width / image_height;

    const int samples = 200;
    const int max_depth = 50;

    point look_from = point{13, 2, 3};
    point look_at = point{0, 0, 0};
    vec view_up = vec{0, 1, 0};
    color background = color{0.7, 0.8, 1};
    double vertical_field_of_view_degrees = 20;
    double focus_dist = 10;
    double aperture = 0;
    double start_time = 0.0;
    double end_time = 1.0;

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
        case 4:
            std::cout << "Earth" << std::endl;
            world = earth();
            break;
        case 5:
            std::cout << "Simple Light" << std::endl;
            world = simple_light();
            background = color{0, 0, 0};
            look_from = point(26, 3, 6);
            look_at = point(0, 2, 0);
            break;
        default:
        case 6:
            world = cornell_box();
            background = color(0, 0, 0);
            look_from = point{278, 278, -800};
            look_at = point{278, 278, 0};
            vertical_field_of_view_degrees = 40;
            break;
        case 7:
            world = cornell_smoke();
            background = color(0, 0, 0);
            look_from = point{278, 278, -800};
            look_at = point{278, 278, 0};
            vertical_field_of_view_degrees = 40;
            break;
        case 8:
            world = final_scene();
            background = color(0, 0, 0);
            look_from = point{478, 278, -600};
            look_at = point{278, 278, 0};
            vertical_field_of_view_degrees = 40;
            break;
    }

    camera cam{aspect_ratio, look_from, look_at, view_up, vertical_field_of_view_degrees, focus_dist, aperture, start_time, end_time};

    std::shared_ptr<hittable> lights =
        std::make_shared<xz_rectangle>(213, 343, 227, 332, 554, nullptr);

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
                    pixel += ray_color(r, background, world, lights, max_depth);
                }
                out << sample_cast(pixel, samples) << '\n';
            }
        }
        out.close();
    }
    return 0;
}
