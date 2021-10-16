#include "generator.h"

hittable_list random_world() {
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

hittable_list two_spheres() {
    std::shared_ptr<checker_board_texture> checker_board = std::make_shared<checker_board_texture>(color{0.2, 0.3, 0.1},
                                                                                                   color{0.9, 0.9, 0.9});
    std::shared_ptr<checker_board_texture> material_ground = std::make_shared<checker_board_texture>(color(0.2, 0.3, 0.1),
                                                                                                     color(0.9, 0.9, 0.9));

    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 10, 0}, 10, std::make_shared<lambertian>(checker_board)));
    world.push_back(std::make_shared<sphere>(point{0, -10, 0}, 10, std::make_shared<lambertian>(checker_board)));
    return world;
}

hittable_list two_perlin_spheres() {
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

hittable_list earth() {
    std::shared_ptr<image_texture> earth_texture = std::make_shared<image_texture>("./data/earthmap.ppm");
    std::shared_ptr<lambertian> earth_surface_material = std::make_shared<lambertian>(earth_texture);
    hittable_list world;
    world.push_back(std::make_shared<sphere>(point{0, 0, 0}, 2, earth_surface_material));
    return world;
}

hittable_list simple_light() {
    hittable_list world;
    std::shared_ptr<marble_texture> per_tex = std::make_shared<marble_texture>(4, std::make_shared<turbulance_perlin>(7));
    world.push_back(std::make_shared<sphere>(point{0, -1000, 0}, 1000, std::make_shared<lambertian>(per_tex)));
    world.push_back(std::make_shared<sphere>(point{0, 2, 0}, 2, std::make_shared<lambertian>(per_tex)));

    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{4, 4, 4});
    world.push_back(std::make_shared<xy_rectangle>(3, 5, 1, 3, -2, light));
    return world;
}

hittable_list cornell_box() {
    hittable_list world;

    std::shared_ptr<lambertian> red = std::make_shared<lambertian>(color{0.65, 0.05, 0.05});
    std::shared_ptr<lambertian> white = std::make_shared<lambertian>(color{0.73, 0.73, 0.73});
    std::shared_ptr<lambertian> green = std::make_shared<lambertian>(color{0.12, 0.45, 0.15});
    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{15, 15, 15});

    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 555, green));
    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 0, red));
    world.push_back(std::make_shared<flip_face>(std::make_shared<xz_rectangle>(213, 343, 227, 332, 554, light)));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 555, white));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 0, white));
    world.push_back(std::make_shared<xy_rectangle>(0, 555, 0, 555, 555, white));

    // std::shared_ptr<material> aluminium = std::make_shared<metal>(color(0.8, 0.85, 0.88), 0.0);

    std::shared_ptr<hittable> box1 = std::make_shared<box>(point(0, 0, 0), point(165, 330, 165), white);
    box1 = std::make_shared<rotate_y>(box1, 15);
    box1 = std::make_shared<translate>(box1, vec(265, 0, 295));
    world.push_back(box1);

    // std::shared_ptr<hittable> box2 = std::make_shared<box>(point(0, 0, 0), point(165, 165, 165), white);
    // box2 = std::make_shared<rotate_y>(box2, -18);
    // box2 = std::make_shared<translate>(box2, vec(130, 0, 65));
    // world.push_back(box2);

    world.push_back(std::make_shared<sphere>(point{190, 90, 190}, 90, std::make_shared<dielectric>(1.5)));

    return world;
}

hittable_list cornell_smoke() {
    hittable_list world;

    std::shared_ptr<lambertian> red = std::make_shared<lambertian>(color{0.65, 0.05, 0.05});
    std::shared_ptr<lambertian> white = std::make_shared<lambertian>(color{0.73, 0.73, 0.73});
    std::shared_ptr<lambertian> green = std::make_shared<lambertian>(color{0.12, 0.45, 0.15});
    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{7, 7, 7});

    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 555, green));
    world.push_back(std::make_shared<yz_rectangle>(0, 555, 0, 555, 0, red));
    world.push_back(std::make_shared<xz_rectangle>(113, 443, 127, 432, 554, light));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 555, white));
    world.push_back(std::make_shared<xz_rectangle>(0, 555, 0, 555, 0, white));
    world.push_back(std::make_shared<xy_rectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<hittable> box_1 = std::make_shared<box>(point{0, 0, 0}, point{165, 330, 165}, white);
    box_1 = std::make_shared<translate>(box_1, vec{265, 0, 295});
    box_1 = std::make_shared<rotate_y>(box_1, 15);
    world.push_back(std::make_shared<constant_medium>(box_1, 0.01, color{0, 0, 0}));

    std::shared_ptr<hittable> box_2 = std::make_shared<box>(point{0, 0, 0}, point{165, 165, 165}, white);
    box_2 = std::make_shared<translate>(box_2, vec{130, 0, 65});
    box_2 = std::make_shared<rotate_y>(box_2, -18);
    world.push_back(std::make_shared<constant_medium>(box_2, 0.01, color{1, 1, 1}));

    return world;
}

hittable_list final_scene() {
    hittable_list box_1;
    std::shared_ptr<lambertian> ground = std::make_shared<lambertian>(color{0.48, 0.83, 0.53});
    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            double w = 100.0;
            double x_0 = -1000.0 + i * w;
            double z_0 = -1000.0 + j * w;
            double y_0 = 0.0;
            double x_1 = x_0 + w;
            double y_1 = random_double(1, 101);
            double z_1 = z_0 + w;
            box_1.push_back(std::make_shared<box>(point{x_0, y_0, z_0}, point{x_1, y_1, z_1}, ground));
        }
    }
    hittable_list world;
    world.push_back(std::make_shared<bvh_node>(box_1, 0, 1));

    std::shared_ptr<diffuse_light> light = std::make_shared<diffuse_light>(color{7, 7, 7});
    world.push_back(std::make_shared<xz_rectangle>(123, 423, 147, 412, 554, light));

    point center_1 = point{400, 400, 200};
    point center_2 = center_1 + point{30, 0, 0};
    std::shared_ptr<dielectric> glass = std::make_shared<dielectric>(1.5);
    std::shared_ptr<lambertian> moving_sphere_material = std::make_shared<lambertian>(color{0.7, 0.3, 0.1});
    world.push_back(std::make_shared<moving_sphere>(center_1, center_2, 0, 1, 50, moving_sphere_material));

    world.push_back(std::make_shared<sphere>(point{260, 150, 45}, 50, glass));
    world.push_back(std::make_shared<sphere>(point{0, 150, 145}, 50, std::make_shared<metal>(color{0.8, 0.8, 0.9}, 1.0)));

    std::shared_ptr<sphere> boundary = std::make_shared<sphere>(point{360, 150, 145}, 70, glass);
    world.push_back(boundary);
    world.push_back(std::make_shared<constant_medium>(boundary, 0.2, color{0.2, 0.4, 0.9}));

    boundary = std::make_shared<sphere>(point{0, 0, 0}, 5000, glass);
    world.push_back(std::make_shared<constant_medium>(boundary, eps, color{1, 1, 1}));

    std::shared_ptr<lambertian> emat = std::make_shared<lambertian>(std::make_shared<image_texture>("./data/earthmap.ppm"));
    world.push_back(std::make_shared<sphere>(point{400, 200, 400}, 100, emat));

    std::shared_ptr<marble_texture> per_tex = std::make_shared<marble_texture>(0.1, std::make_shared<turbulance_perlin>(7));
    world.push_back(std::make_shared<sphere>(point{220, 280, 300}, 80, std::make_shared<lambertian>(per_tex)));

    hittable_list box_2;
    std::shared_ptr<lambertian> white = std::make_shared<lambertian>(color{0.73, 0.73, 0.73});
    for (int i = 0; i < 1000; i++) {
        box_2.push_back(std::make_shared<sphere>(point::random(0, 165), 10, white));
    }

    world.push_back(std::make_shared<translate>(
        std::make_shared<rotate_y>(
            std::make_shared<bvh_node>(box_2, 0, 1), 15),
        vec{-100, 270, 395}));

    return world;
}
