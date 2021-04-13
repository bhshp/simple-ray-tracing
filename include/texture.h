#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "color.h"

struct texture {
   public:
    virtual ~texture();
    virtual color value(double u, double v, const point &p) const = 0;
};

struct solid_color : public texture {
   public:
    solid_color();
    solid_color(const color &c);
    solid_color(double r, double g, double b);
    virtual ~solid_color();

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

// Implementation

inline texture::~texture() {}

inline solid_color::solid_color() {}

inline solid_color::solid_color(const color &c) : color_{c} {}

inline solid_color::solid_color(double r, double g, double b) : color_{r, g, b} {}

inline solid_color::~solid_color() {}

inline color solid_color::value(double, double, const point &) const { return color_; }

inline checker_board_texture::checker_board_texture() {}

inline checker_board_texture::checker_board_texture(const std::shared_ptr<texture> even,
                                                    const std::shared_ptr<texture> odd) : even_{even}, odd_{odd} {}

inline checker_board_texture::checker_board_texture(const color &a,
                                                    const color &b) : even_{std::make_shared<solid_color>(a)},
                                                                      odd_{std::make_shared<solid_color>(b)} {}

inline color checker_board_texture::value(double u, double v, const point &p) const {
    return (std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z()) < 0 ? odd_ : even_)->value(u, v, p);
}

#endif  // TEXTURE_H_
