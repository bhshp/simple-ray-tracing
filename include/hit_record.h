#pragma once

#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

#include <memory>

#include "vec.h"

struct material;

struct hit_record {
   public:
    hit_record(double t,
               const point& p,
               const vec& normal,
               bool front_face,
               const std::shared_ptr<material>& mat = nullptr,
               double u = 0.0,
               double v = 0.0);

    double t() const;
    point p() const;
    vec normal() const;
    bool front_face() const;
    std::shared_ptr<material> mat() const;
    double u() const;
    double v() const;

   private:
    double t_;
    point p_;
    vec normal_;
    bool front_face_;
    std::shared_ptr<material> mat_;
    double u_;
    double v_;
};

#endif  // HIT_RECORD_H_
