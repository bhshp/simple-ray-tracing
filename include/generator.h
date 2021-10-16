#pragma once

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "compact.h"

hittable_list random_world();

hittable_list small_world();

hittable_list two_spheres();

hittable_list two_perlin_spheres();

hittable_list earth();

hittable_list simple_light();

hittable_list cornell_box();

hittable_list cornell_smoke();

hittable_list final_scene();

#endif  // GENERATOR_H_
