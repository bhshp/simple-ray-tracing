#pragma once

#ifndef ORTHO_H_
#define ORTHO_H_

#include "vec.h"

struct ortho {
   public:
    ortho();
    ortho(const vec& v);

    const vec& operator[](size_t index) const;

    vec u() const;
    vec v() const;
    vec w() const;

    vec local(double a, double b, double c) const;
    vec local(const vec& v) const;

   private:
    vec w_, v_, u_;
};

#endif  // ORTHO_H_
