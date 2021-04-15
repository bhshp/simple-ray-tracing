#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>

#include "color.h"
#include "perlin.h"

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

inline image_texture::image_texture() : data_{}, width_{0}, height_{0} {}

inline image_texture::image_texture(const char *const path) {
    const double ratio = 1.0 / 255.0;
    std::ifstream in{path};
    if (!in.is_open()) {
        std::cerr << "File " << path << " Not Exist" << std::endl;
        return;
    }
    in.tie(nullptr);
    std::string type;
    if (!(in >> type) || type != "P3") {
        return;
    }
    if (!(in >> width_) || !(in >> height_)) {
        return;
    }
    if (!(in >> type) || type != "255") {
        return;
    }
    data_.resize(height_);
    for (size_t i = height_ - 1; ; i--) {
        data_[i].resize(width_);
        for (size_t j = 0; j < width_; j++) {
            int r, g, b;
            if (!(in >> r) || !(in >> g) || !(in >> b)) {
                data_.clear();
                decltype(data_){}.swap(data_);
                return;
            }
            data_[i][j] = color{b * ratio, r * ratio, g * ratio};
        }
        if (i == 0) {
            break;
        }
    }
}

inline image_texture::~image_texture() {}

inline color image_texture::value(double u, double v, const point &) const {
    if (data_.empty()) {
        return color{1, 1, 1};
    }
    int i = clamp(static_cast<int>(clamp(v, 0.0, 1.0) * height_), 0, height_ - 1);
    int j = clamp(static_cast<int>(clamp(u, 0.0, 1.0) * width_), 0, width_ - 1);
    return data_[i][j];
}

#endif  // TEXTURE_H_
