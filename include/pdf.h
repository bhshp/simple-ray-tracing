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

#endif  // PDF_H_
