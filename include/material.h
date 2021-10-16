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

#endif  // MATERIAL_H_
