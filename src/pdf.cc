#include "pdf.h"

pdf::~pdf() {}

cosine_pdf::cosine_pdf(const vec &w) : uvw_{w} {}

vec cosine_pdf::generate() const {
    return uvw_.local(random_cosine_direction());
}

double cosine_pdf::value(const vec &direction) const {
    double cosine = direction.unit() * uvw_.w();
    return cosine <= 0 ? 0 : cosine / pi;
}

hittable_pdf::hittable_pdf(const std::shared_ptr<hittable> &p,
                                  const point &origin) : p_{p},
                                                         origin_{origin} {}

vec hittable_pdf::generate() const {
    return p_->random(origin_);
}

double hittable_pdf::value(const vec &direction) const {
    return p_->pdf_value(origin_, direction);
}

mixture_pdf::mixture_pdf(const std::shared_ptr<pdf> &a, const std::shared_ptr<pdf> &b) : a_{a}, b_{b} {}

vec mixture_pdf::generate() const {
    return (random_double() < 0.5 ? a_ : b_)->generate();
}

double mixture_pdf::value(const vec &direction) const {
    return 0.5 * (a_->value(direction) + b_->value(direction));
}

