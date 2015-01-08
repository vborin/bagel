//
// BAGEL - Parallel electron correlation program.
// Filename: moldenio.cc
// Copyright (C) 2012 Shane Parker
//
// Author: Shane Parker <shane.parker@u.northwestern.edu>
// Maintainer: NU theory
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

#include <src/util/io/moldenio.h>

using namespace bagel;
using namespace std;

/************************************************************************************
************************************************************************************/

MoldenIO::MoldenIO(const string filename) : FileIO(filename) {
  const_scales();
  const_maps();
}

void MoldenIO::const_scales() {
  vector<double> s_scale = { 1.0 };
  vector<double> p_scale = { 1.0, 1.0, 1.0 };
  vector<double> d_scale = { 1.0, sqrt(3.0), 1.0, sqrt(3.0), sqrt(3.0), 1.0 };
  vector<double> f_scale = { 1.0, sqrt(5.0), sqrt(5.0), 1.0, sqrt(5.0), sqrt(15.0), sqrt(5.0), sqrt(5.0), sqrt(5.0), 1.0 };
  vector<double> g_scale = { 1.0, sqrt(7.0), sqrt(35.0/3.0), sqrt(7.0), 1.0, sqrt(7.0), sqrt(35.0), sqrt(35.0), sqrt(7.0), sqrt(35.0/3.0), sqrt(35.0), sqrt(35.0/3.0), sqrt(7.0), sqrt(7.0), 1.0 };


  scaling_.push_back(s_scale);
  scaling_.push_back(p_scale);
  scaling_.push_back(d_scale);
  scaling_.push_back(f_scale);
  scaling_.push_back(g_scale);
}

void MoldenIO::const_maps() {
  /************************************************************
  * Build maps from Molden ordering to BAGEL ordering.       *
  ************************************************************/
  {
    vector<int> cart_s_order = { 0 };
    vector<int> cart_p_order = { 0, 1, 2 };
    vector<int> cart_d_order = { 0, 3, 1, 4, 5, 2 };
    vector<int> cart_f_order = { 0, 4, 3, 1, 5, 9, 8, 6, 7, 2 };
    vector<int> cart_g_order = { 0, 3, 9, 5, 1, 4,12,13, 6,10,14,11, 7, 8, 2};

    m2b_cart_ = vector<vector<int>>{cart_s_order, cart_p_order, cart_d_order, cart_f_order, cart_g_order};

    vector<int> sph_s_order = { 0 };
    vector<int> sph_p_order = { 0, 1, 2 };
    vector<int> sph_d_order = { 3, 4, 1, 2, 0 };
    vector<int> sph_f_order = { 5, 6, 3, 4, 1, 2, 0 };
    vector<int> sph_g_order = { 7, 8, 5, 6, 3, 4, 1, 2, 0 };

    m2b_sph_ = vector<vector<int>>{sph_s_order, sph_p_order, sph_d_order, sph_f_order, sph_g_order};
  }

  /************************************************************
  * Build maps from BAGEL ordering to Molden ordering.       *
  ************************************************************/
  {
    vector<int> cart_s_order = { 0 };
    vector<int> cart_p_order = { 0, 1, 2 };
    vector<int> cart_d_order = { 0, 2, 5, 1, 3, 4 };
    vector<int> cart_f_order = { 0, 3, 9, 2, 1, 4, 7, 8, 6, 5 };
    vector<int> cart_g_order = { 0, 4,14, 1, 5, 3, 8,12,13, 2, 9,11, 6, 7,10};

    b2m_cart_ = vector<vector<int>>{cart_s_order, cart_p_order, cart_d_order, cart_f_order, cart_g_order};

    vector<int> sph_s_order = { 0 };
    vector<int> sph_p_order = { 0, 1, 2 };
    vector<int> sph_d_order = { 4, 2, 3, 0, 1 };
    vector<int> sph_f_order = { 6, 4, 5, 2, 3, 0, 1 };
    vector<int> sph_g_order = { 8, 6, 7, 4, 5, 2, 3, 0, 1};

    b2m_sph_ = vector<vector<int>>{sph_s_order, sph_p_order, sph_d_order, sph_f_order, sph_g_order};
  }
}

double MoldenIO::denormalize(int l, double alpha) {
   double denom = 1.0;
   for (int ii = 2; ii <= l; ++ii) denom *= 2 * ii - 1;
   const double value = pow(2.0 * alpha / pi__, 0.75) * pow(sqrt(4.0 * alpha), static_cast<double>(l)) / sqrt(denom);

   return 1.0 / value;
}
