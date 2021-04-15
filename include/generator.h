#pragma once

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "compact.h"

// Declaration

hittable_list random_world();

hittable_list small_world();

hittable_list two_spheres();

hittable_list two_perlin_spheres();

hittable_list earth();

hittable_list simple_light();

// Implementation

inline hittable_list random_world() {
    hittable_list world;

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
    world.push_back(std::make_shared<sphere>(point{-4, 1, 0}, 1.0, std::make_shared<lambertian>(color{0.4, 0.2, 0.1})));
    world.push_back(std::make_shared<sphere>(point{4, 1, 0}, 1.0, std::make_shared<metal>(color{0.7, 0.6, 0.5}, 0.0)));

    std::shared_ptr<checker_board_texture> material_ground = std::make_shared<checker_board_texture>(color(0.2, 0.3, 0.1),
                                                                                                     color(0.9, 0.9, 0.9));

    world.push_back(std::make_shared<sphere>(point{0, -1000, 0}, 1000, std::make_shared<lambertian>(material_ground)));

    hittable_list ret_world;

    ret_world.push_back(std::make_shared<bvh_node>(world, 0.0, 1.0));

    return ret_world;
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

inline hittable_list two_spheres() {
    std::shared_ptr<checker_board_texture> checker_board = std::make_shared<checker_board_texture>(color{0.2, 0.3, 0.1},
                                                                                                   color{0.9, 0.9, 0.9});
    std::shared_ptr<checker_board_texture> material_ground = std::make_shared<checker_board_texture>(color(0.2, 0.3, 0.1),
                                                                                                     color(0.9, 0.9, 0.9));

    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 10, 0}, 10, std::make_shared<lambertian>(checker_board)));
    world.push_back(std::make_shared<sphere>(point{0, -10, 0}, 10, std::make_shared<lambertian>(checker_board)));
    return world;
}

inline hittable_list two_perlin_spheres() {
    hittable_list world;
    std::shared_ptr<marble_texture> per_tex =
        std::make_shared<marble_texture>(4.0, std::make_shared<turbulance_perlin>(7));
    world.push_back(std::make_shared<sphere>(point{0, -1000, 0},
                                             1000,
                                             std::make_shared<lambertian>(per_tex)));
    world.push_back(std::make_shared<sphere>(point{0, 2, 0},
                                             2,
                                             std::make_shared<lambertian>(per_tex)));
    return world;
}

inline hittable_list earth() {
    std::shared_ptr<image_texture> earth_texture = std::make_shared<image_texture>("./data/earthmap.ppm");
    std::shared_ptr<lambertian> earth_surface_material = std::make_shared<lambertian>(earth_texture);
    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 0, 0}, 2, earth_surface_material));
    return world;
}

inline hittable_list simple_light() {
    hittable_list world;
    std::shared_ptr<marble_texture> per_tex = std::make_shared<marble_texture>(4, std::make_shared<turbulance_perlin>(7));
    world.push_back(std::make_shared<sphere>(point{0, -1000, 0}, 1000, std::make_shared<lambertian>(per_tex)));
    world.push_back(std::make_shared<sphere>(point{0, 2, 0}, 2, std::make_shared<lambertian>(per_tex)));

    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{4, 4, 4});
    world.push_back(std::make_shared<xy_rectangle>(3, 5, 1, 3, -2, light));
    return world;
}

inline hittable_list cornell_box() {
    hittable_list world;

    std::shared_ptr<lambertian> red = std::make_shared<lambertian>(color{0.65, 0.05, 0.05});
    std::shared_ptr<lambertian> white = std::make_shared<lambertian>(color{0.73, 0.73, 0.73});
    std::shared_ptr<lambertian> green = std::make_shared<lambertian>(color{0.12, 0.45, 0.15});
    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{15, 15, 15});

    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 555, green));
    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 0, red));
    world.push_back(std::make_shared<xz_rectangle>(213, 343, 227, 332, 554, light));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 0, white));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 555, white));
    world.push_back(std::make_shared<xy_rectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<hittable> box_1 = std::make_shared<box>(point{0, 0, 0}, point{165, 330, 165}, white);
    box_1 = std::make_shared<translate>(box_1, vec{265, 0, 295});
    box_1 = std::make_shared<rotate_y>(box_1, 15);
    world.push_back(box_1);

    std::shared_ptr<hittable> box_2 = std::make_shared<box>(point{0, 0, 0}, point{165, 165, 165}, white);
    box_2 = std::make_shared<translate>(box_2, vec{130, 0, 65});
    box_2 = std::make_shared<rotate_y>(box_2, -18);
    world.push_back(box_2);

    return world;
}

#endif  // GENERATOR_H_
