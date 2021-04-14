#pragma once

#ifndef COMMON_H_
#define COMMON_H_

#include "aabb.h"
#include "bvh_node.h"
#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "hit_record.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "perlin.h"
#include "ray.h"
#include "sphere.h"
#include "stb_image_wrapper.h"
#include "texture.h"
#include "util.h"
#include "vec.h"

// Alias
using hit_result_type = std::optional<hit_record>;

// Initialize And Config
extern const char *const path = "./target/out.ppm";

extern const int image_width = 1920;
extern const int image_height = 1080;

extern const int samples = 50;
extern const int max_depth = 10;

#endif  // COMMON_H_
