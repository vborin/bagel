//
// BAGEL - Parallel electron correlation program.
// Filename: complexeribatch.cc
// Copyright (C) 2009 Toru Shiozaki
//
// Author: Ryan D. Reynolds <rreynoldschem@u.northwestern.edu>
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

#include <src/integral/comprys/complexeribatch.h>
#include <src/integral/comprys/comperirootlist.h>
#include <complex>

using namespace std;
using namespace bagel;

ComplexERIBatch::ComplexERIBatch(const array<shared_ptr<const Shell>,4>& _info, const double max_density, const std::complex<double> dummy, const bool dum,
                   shared_ptr<StackMem> stack)  :  ERIBatch_Base(_info, 0.0, 0, 0, stack) {

// TODO Integral screening has not yet been implemented for London orbitals.  If we want to use integral screening,
// then the second argument to the constructor of ERIBatch_Base should be max_density.  Since we currently pass
// 0.0 as an argument, it should compute every integral.


#ifdef LIBINT_INTERFACE
  assert(false);
#endif

//  root_weight(this->primsize_);
}


void ComplexERIBatch::root_weight(const int ps) {
  if (breit_ == 0) {
    complexeriroot__.root(rank_, T_, roots_, weights_, ps);
  } else {
    assert(0);
    throw runtime_error("Relativistic calculations have not been set up for London orbitals");
  }
}


// TODO For efficiency's sake, it's probably best to find a way to avoid repeatedly running basisinfo_[i]->vector_potential(j) each time we want to get a P or Q value
inline std::complex<double> ComplexERIBatch::get_PQ (const double coord1, const double coord2, const double exp1, const double exp2, const double one12, const int center1, const int dim) {
  const double Areal = coord1*exp1;
  const double Breal = coord2*exp2;
  const double Aimag = -0.5*basisinfo_[center1]->vector_potential(dim);
  const double Bimag = -0.5*basisinfo_[center1+1]->vector_potential(dim);
  const std::complex<double> num ( (Areal + Breal) , (Aimag + Bimag) );
  return ( num * one12 );
}

// no screening for London orbitals at this point
//void ComplexERIBatch::screen_CD() {}

// no screening for London orbitals at this point
//void ComplexERIBatch::screen_AB() {}


//void ComplexERIBatch::save_ssss() {}

