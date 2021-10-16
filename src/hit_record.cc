#include "hit_record.h"

hit_record::hit_record(double t,
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

double hit_record::t() const { return t_; }

point hit_record::p() const { return p_; }

vec hit_record::normal() const { return normal_; }

bool hit_record::front_face() const { return front_face_; }

std::shared_ptr<material> hit_record::mat() const { return mat_; }

double hit_record::u() const { return u_; }

double hit_record::v() const { return v_; }
