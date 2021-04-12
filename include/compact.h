#pragma once

#ifndef COMMON_H_
#define COMMON_H_

#include "camera.h"
#include "color.h"
#include "hit_record.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "vec.h"

// Alias
using hit_result_type = std::optional<hit_record>;

// Initialize And Config
extern const char *const path = "./target/out.ppm";

#endif  // COMMON_H_
