#pragma once

#ifndef PDF_H_
#define PDF_H_

#include <memory>

#include "hittable.h"
#include "ortho.h"
#include "vec.h"

struct pdf {
   public:
    virtual ~pdf();
    virtual vec generate() const = 0;
    virtual double value(const vec &direction) const = 0;
};

struct cosine_pdf : public pdf {
   public:
    cosine_pdf(const vec &w);
    virtual vec generate() const override;
    virtual double value(const vec &direction) const override;

   private:
    ortho uvw_;
};

struct hittable_pdf : public pdf {
   public:
    hittable_pdf(const std::shared_ptr<hittable> &p, const point &origin);
    virtual vec generate() const override;
    virtual double value(const vec &direction) const override;

   private:
    std::shared_ptr<hittable> p_;
    point origin_;
};

struct mixture_pdf : public pdf {
   public:
    mixture_pdf(const std::shared_ptr<pdf> &a, const std::shared_ptr<pdf> &b);
    virtual vec generate() const override;
    virtual double value(const vec &direction) const override;

   private:
    std::shared_ptr<pdf> a_, b_;
};

// Implementation

inline pdf::~pdf() {}

inline cosine_pdf::cosine_pdf(const vec &w) : uvw_{w} {}

inline vec cosine_pdf::generate() const {
    return uvw_.local(random_cosine_direction());
}

inline double cosine_pdf::value(const vec &direction) const {
    double cosine = direction.unit() * uvw_.w();
    return cosine <= 0 ? 0 : cosine / pi;
}

inline hittable_pdf::hittable_pdf(const std::shared_ptr<hittable> &p,
                                  const point &origin) : p_{p},
                                                         origin_{origin} {}

inline vec hittable_pdf::generate() const {
    return p_->random(origin_);
}

inline double hittable_pdf::value(const vec &direction) const {
    return p_->pdf(origin_, direction);
}

inline mixture_pdf::mixture_pdf(const std::shared_ptr<pdf> &a, const std::shared_ptr<pdf> &b) : a_{a}, b_{b} {}

inline vec mixture_pdf::generate() const {
    return (random_double() < 0.5 ? a_ : b_)->generate();
}

inline double mixture_pdf::value(const vec &direction) const {
    return 0.5 * (a_->value(direction) + b_->value(direction));
}

#endif  // PDF_H_
