#pragma once

#ifndef CONFIG_H_
#define CONFIG_H_

const int width_ratio = 16;
const int height_ratio = 9;

const double aspect_ratio = 1.0 * width_ratio / height_ratio;

const int image_width = 1600;
const int image_height = static_cast<int>(1.0 * image_width / aspect_ratio);

const double viewport_height = 2.0;
const double viewport_width = aspect_ratio * viewport_height;
const double focal_length = 1.0;

const char* const path = "./target/out.ppm";

#endif
