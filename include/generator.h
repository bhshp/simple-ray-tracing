#pragma once

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "hittable_list.h"

// Declaration

hittable_list random_world();

hittable_list small_world();

// Implementation

inline hittable_list random_world() {
    hittable_list world;

    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.5});
    world.push_back(std::make_shared<sphere>(point{0, -1000, 0}, 1000, material_ground));

    for (int i = -11; i <= 11; i++) {
        for (int j = -11; j <= 11; j++) {
            double choose = random_double();
            point center{i + 0.9 * random_double(), 0.2, j + 0.9 * random_double()};
            if ((center - point{4, 0.2, 0}).length() > 0.9) {
                std::shared_ptr<material> sphere_material;
                if (choose < 0.5) {
                    // diffuse
                    color albedo = random_color() % random_color();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    point center_2 = center + vec{0, random_double(0, 0.5), 0};
                    world.push_back(std::make_shared<moving_sphere>(center, center_2, 0.0, 1.0, 0.2, sphere_material));
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

    return world;
}

inline hittable_list small_world() {
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

#endif  // GENERATOR_H_
