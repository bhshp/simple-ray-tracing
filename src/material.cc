#include "material.h"

scatter_record::scatter_record() {}

scatter_record::scatter_record(const color &c, const ray &r, const std::shared_ptr<pdf> &p) : albedo_{c}, r_{r}, pdf_{p} {}

scatter_record::~scatter_record() {}

color scatter_record::albedo() const { return albedo_; }

ray scatter_record::r() const { return r_; }

std::shared_ptr<pdf> scatter_record::pdf_ptr() const { return pdf_; }

material::material() {}

material::~material() {}

color material::emit(const ray &, const hit_record &, double, double, const point &) const {
    return color{0, 0, 0};
}

double material::pdf_value(const ray &, const hit_record &, const ray &) const {
    return 1;
}

scatter_result_type material::scatter(const ray &, const hit_record &) const {
    return std::nullopt;
}

lambertian::lambertian(const color &c) : albedo_{std::make_shared<solid_color_texture>(c)} {}

lambertian::lambertian(const std::shared_ptr<texture> &c) : albedo_{c} {}

lambertian::~lambertian() {}

std::shared_ptr<texture> lambertian::albedo() const { return albedo_; }

scatter_result_type lambertian::scatter(const ray &in, const hit_record &rec) const {
    ortho uvw{rec.normal()};
    vec direction = uvw.local(random_cosine_direction());
    ray scattered{rec.p(), direction.unit(), in.time()};
    return scatter_result_type{
        std::in_place,
        albedo_->value(rec.u(), rec.v(), rec.p()),
        scattered,
        std::make_shared<cosine_pdf>(rec.normal())};
}

double lambertian::pdf_value(const ray &, const hit_record &rec, const ray &scattered) const {
    double cosine = rec.normal() * scattered.direction().unit();
    return cosine < 0 ? 0 : cosine / pi;
}

metal::metal(const color &a, double f) : albedo_{a}, fuzz_{f} {}

metal::~metal() {}

color metal::albedo() const { return albedo_; }

scatter_result_type metal::scatter(const ray &in, const hit_record &rec) const {
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

dielectric::dielectric(double refraction) : refraction_{refraction} {}

dielectric::~dielectric() {}

scatter_result_type dielectric::scatter(const ray &in, const hit_record &rec) const {
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

double dielectric::reflectance(double cos, double ratio) {
    // Schlick approximate
    double r0 = sqr((1 - ratio) / (1 + ratio));
    return r0 + (1 - r0) * pow(1 - cos, 5);
}

diffuse_light::diffuse_light(color c) : emit_{std::make_shared<solid_color_texture>(c)} {}

diffuse_light::diffuse_light(const std::shared_ptr<texture> &p) : emit_{p} {}

diffuse_light::~diffuse_light() {}

color diffuse_light::emit(const ray &, const hit_record &rec, double u, double v, const point &p) const {
    return rec.front_face() ? emit_->value(u, v, p) : color{};
}

scatter_result_type diffuse_light::scatter(const ray &, const hit_record &) const {
    return std::nullopt;
}

isotropic::isotropic(const color &c) : albedo_{std::make_shared<solid_color_texture>(c)} {}

isotropic::isotropic(const std::shared_ptr<texture> &t) : albedo_{t} {}

scatter_result_type isotropic::scatter(const ray &in, const hit_record &rec) const {
    return scatter_result_type{
        std::in_place,
        albedo_->value(rec.u(), rec.v(), rec.p()),
        ray{rec.p(), random_in_unit_sphere(), in.time()},
        nullptr};
}
