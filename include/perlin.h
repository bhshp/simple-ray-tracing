#pragma once

#ifndef PERLIN_H_
#define PERLIN_H_

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

#include "vec.h"

struct perlin {
   public:
    perlin();
    virtual ~perlin();
    virtual double noise(const point &p) const;

   protected:
    static const int point_count = 256;

    static std::array<int, point_count> generate_and_shuffle();

    double calculate_noise(const point &p) const;

    std::array<vec, point_count> random_vec_;
    std::array<int, point_count> perm_x_;
    std::array<int, point_count> perm_y_;
    std::array<int, point_count> perm_z_;
};

struct smooth_perlin : perlin {
   public:
    smooth_perlin();
    virtual ~smooth_perlin();
    virtual double noise(const point &p) const override;
};

struct turbulance_perlin : perlin {
   public:
    turbulance_perlin();
    turbulance_perlin(int depth);
    virtual ~turbulance_perlin();
    virtual double noise(const point &p) const override;

   private:
    const int depth_;
};

#endif  // PERLIN_H_
