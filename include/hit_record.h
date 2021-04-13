#pragma once

#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

#include <memory>

#include "vec.h"  // point vec

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

inline hit_record::hit_record(double t,
                              const point& p,
                              const vec& normal,
                              bool front_face,
                              const std::shared_ptr<material>& mat,
                              double u,
                              double v) : t_{t},
                                          p_{p},
                                          normal_{normal},
                                          front_face_{front_face},
                                          mat_{mat},
                                          u_{u},
                                          v_{v} {}

inline double hit_record::t() const { return t_; }

inline point hit_record::p() const { return p_; }

inline vec hit_record::normal() const { return normal_; }

inline bool hit_record::front_face() const { return front_face_; }

inline std::shared_ptr<material> hit_record::mat() const { return mat_; }

inline double hit_record::u() const { return u_; }

inline double hit_record::v() const { return v_; }

#endif  // HIT_RECORD_H_
