#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>

#include "color.h"
#include "perlin.h"
#include "stb_image_wrapper.h"

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
    constexpr static int bytes_per_pixel = 3;
    constexpr static double ratio = 1.0 / 255.0;

    unsigned char *data_;
    int width_;
    int height_;
    int col_bytes_;
};

// Implementation

inline texture::~texture() {}

inline solid_color_texture::solid_color_texture() {}

inline solid_color_texture::solid_color_texture(const color &c) : color_{c} {}

inline solid_color_texture::solid_color_texture(double r, double g, double b) : color_{r, g, b} {}

inline solid_color_texture::~solid_color_texture() {}

inline color solid_color_texture::value(double, double, const point &) const { return color_; }

inline checker_board_texture::checker_board_texture() {}

inline checker_board_texture::checker_board_texture(const std::shared_ptr<texture> even,
                                                    const std::shared_ptr<texture> odd) : even_{even}, odd_{odd} {}

inline checker_board_texture::checker_board_texture(const color &a,
                                                    const color &b) : even_{std::make_shared<solid_color_texture>(a)},
                                                                      odd_{std::make_shared<solid_color_texture>(b)} {}

inline color checker_board_texture::value(double u, double v, const point &p) const {
    return (std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z()) < 0 ? odd_ : even_)->value(u, v, p);
}

inline noise_texture::noise_texture(double scale,
                                    const std::shared_ptr<perlin> &p) : scale_{scale},
                                                                        noise_{p} {}

inline noise_texture::~noise_texture() {}

inline color noise_texture::value(double, double, const point &p) const {
    return (noise_->noise(scale_ * p) + 1) * 0.5 * color{1, 1, 1};
}

inline marble_texture::marble_texture(double scale,
                                      const std::shared_ptr<perlin> &p) : scale_{scale},
                                                                          noise_{p} {}

inline marble_texture::~marble_texture() {}

inline color marble_texture::value(double, double, const point &p) const {
    return 0.5 * (1 + std::sin(scale_ * p.z() + 10 * noise_->noise(p))) * color{1, 1, 1};
}

inline image_texture::image_texture() : data_{nullptr}, width_{0}, height_{0}, col_bytes_{0} {}

inline image_texture::image_texture(const char *const path) {
    int components_per_pixel = bytes_per_pixel;
    if (data_ = stbi_load(path, &width_, &height_, &components_per_pixel, components_per_pixel); data_ == nullptr) {
        std::cerr << "File Not Exist!" << std::endl;
        width_ = height_ = 0;
    }
    col_bytes_ = bytes_per_pixel * width_;
}

inline image_texture::~image_texture() {
    if (data_ != nullptr) {
        delete data_;
    }
}

inline color image_texture::value(double u, double v, const point &) const {
    if (data_ == nullptr) {
        return color{0, 1, 1};
    }
    u = clamp(u, 0.0, 1.0);
    v = 1 - clamp(v, 0.0, 1.0);
    int i = clamp(static_cast<int>(u * width_), 0, width_ - 1);
    int j = clamp(static_cast<int>(v * height_), 0, height_ - 1);
    unsigned char *pixel = &data_[j * col_bytes_ + i * bytes_per_pixel];
    return color{pixel[0] * ratio, pixel[1] * ratio, pixel[2] * ratio};
}

#endif  // TEXTURE_H_
