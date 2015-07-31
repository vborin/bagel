//
// BAGEL - Parallel electron correlation program.
// Filename: gamma.h
// Copyright (C) 2015 Toru Shiozaki
//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//

//

#ifndef __BAGEL_UTIL_MATH_GAMMA_H
#define __BAGEL_UTIL_MATH_GAMMA_H

#include <iostream>
#include <cmath>
#include <vector>
#include <src/util/constants.h>

namespace bagel {

#if 0
class GammaLn { // Lanczos for ln(G(z))

  public:
    GammaLn() { }
    ~GammaLn() { }

    double compute(const double z) const {
    }

    double operator() (const double z) const { assert(z > 0); return compute(z); }
};
#endif

class Gamma_upper { // Upper incomplete gamma function G(l+1/2, x)

  private:

  public:
    Gamma_upper() { }
    ~Gamma_upper() { }

    double compute(const int l, const double x) const {

      if (l > 1200 || x > 300)
        throw std::runtime_error("Failed to compute incomplete gamma function!");

      double gamma = sqrt(pi__) * erfc(sqrt(x));
      for (int i = 1; i <= l; ++i) {
        const double r = i + 0.5;
        gamma = (r-1.0) * gamma + pow(x, r-1.0) * exp(-x);
      }

      return gamma;
    }

    double operator()(const int l, const double x) const { assert(l < 1200 && x < 300); return compute(l, x); }

};

}

#endif
