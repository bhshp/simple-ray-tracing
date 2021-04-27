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
    static const color white = color{1.0, 1.0, 1.0};
    static const color blue{0.5, 0.7, 1.0};
    return mix(white, blue, 0.5 * (r.direction().unit().y() + 1.0));
}

hittable_list random_world() {
    hittable_list world;

    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.5});
    world.push_back(std::make_shared<sphere>(point{0, -1000, 0}, 1000, material_ground));
    // big sphere as ground

    for (int i = -11; i <= 11; i++) {
        for (int j = -11; j <= 11; j++) {
            double choose = random_double();
            point center{i + 0.9 * random_double(), 0.2, j + 0.9 * random_double()};
            if ((center - point{4, 0.2, 0}).length() > 0.9) {
                std::shared_ptr<material> sphere_material;
                if (choose < 0.3) {
                    // diffuse
                    color albedo = random_color() % random_color();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.push_back(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose < 0.6) {
                    // metal
                    color albedo = random_color(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.push_back(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.push_back(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
 
    world.push_back(std::make_shared<sphere>(point{0, 1, 0}, 1.0, std::make_shared<dielectric>(1.5)));
    world.push_back(std::make_shared<sphere>(point{-4, 1, 0}, 1.0, std::make_shared<lambertian>(color(0.4, 0.2, 0.1))));
    world.push_back(std::make_shared<sphere>(point{4, 1, 0}, 1.0, std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0)));
    // three big balls

    return world;
}

hittable_list small_world() {
    // Materials
    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.0});
    std::shared_ptr<lambertian> material_center = std::make_shared<lambertian>(color{0.1, 0.2, 0.5});
    std::shared_ptr<dielectric> material_left = std::make_shared<dielectric>(1.5);
    std::shared_ptr<metal> material_right = std::make_shared<metal>(color{0.8, 0.6, 0.2}, 1.0);

    // World
    hittable_list world;

    world.push_back(std::make_shared<sphere>(point{0, -100.5, -1}, 100, material_ground));
    world.push_back(std::make_shared<sphere>(point{0, 0, -1}, 0.5, material_center));
    world.push_back(std::make_shared<sphere>(point{-1, 0, -1}, 0.5, material_left));
    world.push_back(std::make_shared<sphere>(point{-1, 0, -1}, -0.4, material_left));
    world.push_back(std::make_shared<sphere>(point{1, 0, -1}, 0.5, material_right));
    return world;
}

int main() {
    canvas cvs{image_width, image_height};

    camera cam{cvs.aspect_ratio(), point{13, 2, 3}, point{0, 0, 0}, vec{0, 1, 0}, 20, 10, 0.1};

    {
        std::ofstream out(path);
        out << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";
        hittable_list world = random_world();
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
