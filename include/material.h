#pragma once

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <optional>
#include <utility>

#include "color.h"
#include "hit_record.h"
#include "ortho.h"
#include "pdf.h"
#include "ray.h"
#include "texture.h"
#include "vec.h"

struct hit_record;

struct scatter_record {
   public:
    scatter_record();
    scatter_record(const color &c, const ray &r, const std::shared_ptr<pdf> &p);
    ~scatter_record();
    color albedo() const;
    ray r() const;
    std::shared_ptr<pdf> pdf_ptr() const;

   private:
    color albedo_;
    ray r_;
    std::shared_ptr<pdf> pdf_;
};

using scatter_result_type = std::optional<scatter_record>;

struct material {
   public:
    material();

    virtual ~material();
    virtual color emit(const ray &in, const hit_record &rec, double u, double v, const point &p) const;
    virtual double pdf_value(const ray &in, const hit_record &rec, const ray &scattered) const;
    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const;
};

struct lambertian : public material {
   public:
    lambertian(const color &c);
    lambertian(const std::shared_ptr<texture> &a);

    virtual ~lambertian();
    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const override;
    virtual double pdf_value(const ray &in, const hit_record &rec, const ray &scattered) const override;

    std::shared_ptr<texture> albedo() const;

   private:
    std::shared_ptr<texture> albedo_;
};

struct metal : public material {
   public:
    metal(const color &a, double f = 1.0);

    virtual ~metal();
    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const override;

    color albedo() const;

   private:
    color albedo_;
    double fuzz_;
};

struct dielectric : public material {
   public:
    dielectric(double refraction);
    virtual ~dielectric();

    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const override;

   private:
    static double reflectance(double cos, double ratio);

    double refraction_;
};

struct diffuse_light : public material {
   public:
    diffuse_light(color c);
    diffuse_light(const std::shared_ptr<texture> &p);
    virtual ~diffuse_light();

    virtual color emit(const ray &in, const hit_record &rec, double u, double v, const point &p) const override;
    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const override;

   private:
    std::shared_ptr<texture> emit_;
};

struct isotropic : public material {
   public:
    isotropic(const color &c);
    isotropic(const std::shared_ptr<texture> &t);

    virtual scatter_result_type scatter(const ray &in, const hit_record &rec) const override;

   private:
    std::shared_ptr<texture> albedo_;
};

// Implementation

inline scatter_record::scatter_record() {}

inline scatter_record::scatter_record(const color &c, const ray &r, const std::shared_ptr<pdf> &p) : albedo_{c}, r_{r}, pdf_{p} {}

inline scatter_record::~scatter_record() {}

inline color scatter_record::albedo() const { return albedo_; }

inline ray scatter_record::r() const { return r_; }

inline std::shared_ptr<pdf> scatter_record::pdf_ptr() const { return pdf_; }

inline material::material() {}

inline material::~material() {}

inline color material::emit(const ray &, const hit_record &, double, double, const point &) const {
    return color{0, 0, 0};
}

inline double material::pdf_value(const ray &, const hit_record &, const ray &) const {
    return 1;
}

inline scatter_result_type material::scatter(const ray &, const hit_record &) const {
    return std::nullopt;
}

inline lambertian::lambertian(const color &c) : albedo_{std::make_shared<solid_color_texture>(c)} {}

inline lambertian::lambertian(const std::shared_ptr<texture> &c) : albedo_{c} {}

inline lambertian::~lambertian() {}

inline std::shared_ptr<texture> lambertian::albedo() const { return albedo_; }

inline scatter_result_type lambertian::scatter(const ray &in, const hit_record &rec) const {
    ortho uvw{rec.normal()};
    vec direction = uvw.local(random_cosine_direction());
    ray scattered{rec.p(), direction.unit(), in.time()};
    return scatter_result_type{
        std::in_place,
        albedo_->value(rec.u(), rec.v(), rec.p()),
        scattered,
        std::make_shared<cosine_pdf>(rec.normal())};
}

inline double lambertian::pdf_value(const ray &, const hit_record &rec, const ray &scattered) const {
    double cosine = rec.normal() * scattered.direction().unit();
    return cosine < 0 ? 0 : cosine / pi;
}

inline metal::metal(const color &a, double f) : albedo_{a}, fuzz_{f} {}

inline metal::~metal() {}

inline color metal::albedo() const { return albedo_; }

inline scatter_result_type metal::scatter(const ray &in, const hit_record &rec) const {
    vec reflected = reflect(in.direction().unit(), rec.normal());
    ray scattered{rec.p(), reflected + fuzz_ * random_in_unit_sphere(), in.time()};
    if (scattered.direction() * rec.normal() <= 0) {
        return std::nullopt;
    }
    return scatter_result_type{std::in_place,
                               albedo(),
                               scattered,
                               nullptr};
    ;
}

inline dielectric::dielectric(double refraction) : refraction_{refraction} {}

inline dielectric::~dielectric() {}

inline scatter_result_type dielectric::scatter(const ray &in, const hit_record &rec) const {
    double ratio = rec.front_face() ? (1.0 / refraction_) : refraction_;
    vec unit_direction = in.direction().unit();
    double cos_theta = std::min(-unit_direction * rec.normal(), 1.0);
    double sin_theta = std::sqrt(1.0 - sqr(cos_theta));
    vec direction = (ratio * sin_theta > 1.0 || reflectance(cos_theta, ratio) > random_double())
                        ? reflect(unit_direction, rec.normal())
                        : refract(unit_direction, rec.normal(), ratio);
    return scatter_result_type{std::in_place,
                               color{1, 1, 1},
                               ray{rec.p(), direction, in.time()},
                               nullptr};
}

inline double dielectric::reflectance(double cos, double ratio) {
    // Schlick approximate
    double r0 = sqr((1 - ratio) / (1 + ratio));
    return r0 + (1 - r0) * pow(1 - cos, 5);
}

inline diffuse_light::diffuse_light(color c) : emit_{std::make_shared<solid_color_texture>(c)} {}

inline diffuse_light::diffuse_light(const std::shared_ptr<texture> &p) : emit_{p} {}

inline diffuse_light::~diffuse_light() {}

inline color diffuse_light::emit(const ray &, const hit_record &rec, double u, double v, const point &p) const {
    return rec.front_face() ? emit_->value(u, v, p) : color{};
}

inline scatter_result_type diffuse_light::scatter(const ray &, const hit_record &) const {
    return std::nullopt;
}

inline isotropic::isotropic(const color &c) : albedo_{std::make_shared<solid_color_texture>(c)} {}

inline isotropic::isotropic(const std::shared_ptr<texture> &t) : albedo_{t} {}

inline scatter_result_type isotropic::scatter(const ray &in, const hit_record &rec) const {
    return scatter_result_type{
        std::in_place,
        albedo_->value(rec.u(), rec.v(), rec.p()),
        ray{rec.p(), random_in_unit_sphere(), in.time()},
        nullptr};
}

#endif  // MATERIAL_H_
