#pragma once

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <optional>
#include <utility>

#include "color.h"
#include "hit_record.h"
#include "ray.h"
#include "vec.h"

struct hit_record;

using scatter_result_type = std::optional<std::pair<color, ray>>;

struct material {
   public:
    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const = 0;
};

struct lambertian : public material {
   public:
    lambertian(const color &c);
    virtual ~lambertian();

    color albedo() const;

    virtual scatter_result_type scatter(const ray &, const hit_record &rec) const override;

   private:
    color albedo_;
};

lambertian::lambertian(const color &c) : albedo_{c} {}

lambertian::~lambertian() {}

color lambertian::albedo() const { return albedo_; }

scatter_result_type lambertian::scatter(const ray &, const hit_record &rec) const {
    vec scatter_direction = rec.normal() + random_in_unit_sphere().unit();
    if (scatter_direction.near_zero()) {
        scatter_direction = rec.normal();
    }
    return std::make_optional<std::pair<color, ray>>(std::make_pair(albedo(), ray{rec.p(), scatter_direction}));
}

struct metal : public material {
   public:
    metal(const color &a, double f = 1.0);
    virtual ~metal();

    color albedo() const;

    virtual scatter_result_type scatter(const ray &, const hit_record &rec) const override;

   private:
    color albedo_;
    double fuzz_;
};

metal::metal(const color &a, double f) : albedo_{a}, fuzz_{f} {}

metal::~metal() {}

color metal::albedo() const { return albedo_; }

scatter_result_type metal::scatter(const ray &in, const hit_record &rec) const {
    vec reflected = reflect(in.direction().unit(), rec.normal());
    ray scattered{rec.p(), reflected + fuzz_ * random_in_unit_sphere()};
    if (scattered.direction() * rec.normal() <= 0) {
        return std::nullopt;
    }
    return std::make_optional<std::pair<color, ray>>(std::make_pair(albedo(), scattered));
}

#endif  // MATERIAL_H_
