#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "color.h"
#include "perlin.h"
#include "vec.h"

struct texture {
   public:
    virtual ~texture();
    virtual color value(double u, double v, const point &p) const = 0;
};

struct solid_color_texture : public texture {
   public:
    solid_color_texture();
    solid_color_texture(const color &c);
    solid_color_texture(double r, double g, double b);
    virtual ~solid_color_texture();

    virtual color value(double u, double v, const point &p) const override;

   private:
    color color_;
};

struct checker_board_texture : public texture {
   public:
    checker_board_texture();
    checker_board_texture(const std::shared_ptr<texture> even,
                          const std::shared_ptr<texture> odd);
    checker_board_texture(const color &a, const color &b);

    virtual color value(double u, double v, const point &p) const override;

   private:
    std::shared_ptr<texture> even_;
    std::shared_ptr<texture> odd_;
};

struct noise_texture : public texture {
   public:
    noise_texture(double scale = 1.0,
                  const std::shared_ptr<perlin> &p = std::make_shared<perlin>());
    virtual ~noise_texture();
    virtual color value(double u, double v, const point &p) const override;

   private:
    double scale_;
    std::shared_ptr<perlin> noise_;
};

struct marble_texture : public noise_texture {
   public:
    marble_texture(double scale = 1.0,
                   const std::shared_ptr<perlin> &p = std::make_shared<turbulance_perlin>());
    virtual ~marble_texture();
    virtual color value(double u, double v, const point &p) const override;

   private:
    double scale_;
    std::shared_ptr<perlin> noise_;
};

struct image_texture : public texture {
   public:
    image_texture();
    image_texture(const char *const path);
    virtual ~image_texture();
    virtual color value(double u, double v, const point &p) const override;

   private:
    std::vector<std::vector<color>> data_;
    size_t width_;
    size_t height_;
};

#endif  // TEXTURE_H_
