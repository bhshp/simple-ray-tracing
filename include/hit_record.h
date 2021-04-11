#pragma once

#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

#include "vec.h"  // point vec

struct hit_record {
   public:
    hit_record(double t, const point& p, const vec& normal, bool front_face);

    double t() const;
    point p() const;
    vec normal() const;
    bool front_face() const;

   private:
    double t_;
    point p_;
    vec normal_;
    bool front_face_;
};

#endif  // HIT_RECORD_H_
