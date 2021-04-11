#include "hit_record.h"

hit_record::hit_record(double t, const point& p, const vec& normal, bool front_face) : t_{t},
                                                                                       p_{p},
                                                                                       normal_{normal},
                                                                                       front_face_{front_face} {}

inline double hit_record::t() const { return t_; }

inline point hit_record::p() const { return p_; }

inline vec hit_record::normal() const { return normal_; }

inline bool hit_record::front_face() const { return front_face_; }
