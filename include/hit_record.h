#pragma once

#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

#include "ray.h"
#include "vec.h"

struct hit_record {
   public:
    hit_record(double t, const point& p, const vec& normal, bool front_face) : t_{t},
                                                                               p_{p},
                                                                               normal_{normal},
                                                                               front_face_{front_face} {}

    inline double t() const { return t_; }
    inline point p() const { return p_; }
    inline vec normal() const { return normal_; }
    inline bool front_face() const { return front_face_; }

   private:
    double t_;
    point p_;
    vec normal_;
    bool front_face_;
};

#endif  // HIT_RECORD_H_