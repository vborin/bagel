//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: rdm.cc
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#include <src/wfn/rdm.h>
#include <src/util/math/algo.h>

using namespace bagel;
using namespace std;


template<>
bool RDM<1>::natural_orbitals() const {
  const double a = ddot_(norb()*norb(), data(), 1, data(), 1);
  const double b = ddot_(norb(), data(), norb()+1, data(), norb()+1);
  return fabs(a-b) < 1.0e-12;
}


template<>
vector<double> RDM<1>::diag() const {
  std::vector<double> out(norb());
  for (int i = 0; i != norb(); ++i) out[i] = element(i,i);
  return out;
}


template<>
pair<shared_ptr<Matrix>, VectorB> RDM<1>::generate_natural_orbitals(const bool occ_sort) const {
  auto buf = make_shared<Matrix>(norb(),norb(),true);
  buf->add_diag(2.0);
  daxpy_(norb()*norb(), -1.0, data(), 1, buf->data(), 1);

  VectorB vec(norb());
  buf->diagonalize(vec);

  for (auto& i : vec) i = 2.0-i;
  auto buf2 = buf->clone();
  VectorB vec2(norb());

  if (occ_sort) {
    // sort by natural orbital occupation numbers
    int b2n = buf2->ndim();
    for (int i = 0; i != buf2->mdim(); ++i) {
      copy_n(buf->element_ptr(0, buf2->mdim()-1-i), b2n, buf2->element_ptr(0, i));
      vec2[b2n-1-i] = vec[i] > 0.0 ? vec[i] : 0.0;;
    }
  } else {
    map<int,int> emap;
    // sort eigenvectors so that buf is close to a unit matrix
    // target column
    for (int i = 0; i != norb(); ++i) {
      // first find the source column
      tuple<int, double> max = make_tuple(-1, 0.0);
      for (int j = 0; j != norb(); ++j)
        if (fabs(buf->element(i,j)) > get<1>(max))
          max = make_tuple(j, fabs(buf->element(i,j)));

      // register to emap
      if (emap.find(get<0>(max)) != emap.end()) throw logic_error("this should not happen. RDM<1>::generate_natural_orbitals()");
      emap.emplace(get<0>(max), i);

      // copy to the target
      copy_n(buf->element_ptr(0,get<0>(max)), norb(), buf2->element_ptr(0,i));
      vec2(i) = vec(get<0>(max));
     }
  }

  // fix the phase
  for (int i = 0; i != norb(); ++i) {
    if (buf2->element(i,i) < 0.0)
      blas::scale_n(-1.0, buf2->element_ptr(0,i), norb());
  }
  return {buf2, vec2};
}


template<>
void RDM<1>::transform(shared_ptr<const Matrix> coeff) {
  auto buf = clone();
  btas::contract(1.0, *this, {0,1}, *coeff, {1,2}, 0.0, *buf, {0,2});
  btas::contract(1.0, *coeff, {1,0}, *buf, {1,2}, 0.0, *this, {0,2});
}


template<>
void RDM<2>::transform(shared_ptr<const Matrix> coeff) {
  const double* start = coeff->data();
  const int dim = norb()*norb();
  unique_ptr<double[]> buf(new double[dim*dim]);
  // first half transformation
  dgemm_("N", "N", dim*norb(), norb(), norb(), 1.0, data(), dim*norb(), start, norb(), 0.0, buf.get(), dim*norb());
  for (int i = 0; i != norb(); ++i)
    dgemm_("N", "N", dim, norb(), norb(), 1.0, buf.get()+i*dim*norb(), dim, start, norb(), 0.0, data()+i*dim*norb(), dim);
  // then tranpose
  blas::transpose(data(), dim, dim, buf.get());
  // and do it again
  dgemm_("N", "N", dim*norb(), norb(), norb(), 1.0, buf.get(), dim*norb(), start, norb(), 0.0, data(), dim*norb());
  for (int i = 0; i != norb(); ++i)
    dgemm_("N", "N", dim, norb(), norb(), 1.0, data()+i*dim*norb(), dim, start, norb(), 0.0, buf.get()+i*dim*norb(), dim);
  // to make sure for non-symmetric density matrices (and anyway this should be cheap).
  blas::transpose(buf.get(), dim, dim, data());
}


template<>
shared_ptr<Matrix> RDM<1>::rdm1_mat(const int nclosed, const bool all) const {
  auto out = make_shared<Matrix>(nclosed+norb(), nclosed+norb());
  if (all)
    for (int i = 0; i != nclosed; ++i) out->element(i,i) = 2.0;
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      out->element(j+nclosed, i+nclosed) = element(j,i);
  return out;
}


template<>
shared_ptr<Matrix> RDM<1>::rdm1_mat_tr(const int nclosed, const bool all) const {
  auto out = make_shared<Matrix>(nclosed+norb(), nclosed+norb());
  if (all)
    for (int i = 0; i != nclosed; ++i) out->element(i,i) = 0.0;
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      out->element(j+nclosed, i+nclosed) = element(j,i);
  return out;
}


template<>
void RDM<1>::print(const double thresh) const {
  const double* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j, ++ptr)
      if (fabs(*ptr) > thresh)
        cout << setw(3) << j << setw(3) << i << setw(12) << setprecision(7) << *ptr << endl;
}


template<>
void ZRDM<1>::print(const double thresh) const {
  const complex<double>* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      cout << setw(20) << setprecision(7) << *ptr++ << endl;
}


template<>
void RDM<2>::print(const double thresh) const {
  const double* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      for (int k = 0; k != norb(); ++k)
        for (int l = 0; l != norb(); ++l, ++ptr)
          if (fabs(*ptr) > thresh)
            cout << setw(3) << l << setw(3)
                      << k << setw(3) << j << setw(3) << i
                      << setw(12) << setprecision(7) << *ptr << endl;
}


template<>
void ZRDM<2>::print(const double thresh) const {
  const complex<double>* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      for (int k = 0; k != norb(); ++k)
        for (int l = 0; l != norb(); ++l, ++ptr)
          if (fabs(*ptr) > thresh)
            cout << setw(3) << l << setw(3)
                      << k << setw(3) << j << setw(3) << i
                      << setw(20) << setprecision(7) << *ptr << endl;
}


template<>
void RDM<3>::print(const double thresh) const {
  const double* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      for (int k = 0; k != norb(); ++k)
        for (int l = 0; l != norb(); ++l)
        for (int m = 0; m != norb(); ++m)
        for (int n = 0; n != norb(); ++n, ++ptr)
          if (fabs(*ptr) > thresh)
            cout << setw(3) << n << setw(3) << m << setw(3) << l << setw(3)
                 << k << setw(3) << j << setw(3) << i
                 << setw(12) << setprecision(7) << *ptr << endl;
}


template<>
void ZRDM<3>::print(const double thresh) const {
  const complex<double>* ptr = data();
  for (int i = 0; i != norb(); ++i)
    for (int j = 0; j != norb(); ++j)
      for (int k = 0; k != norb(); ++k)
        for (int l = 0; l != norb(); ++l)
        for (int m = 0; m != norb(); ++m)
        for (int n = 0; n != norb(); ++n, ++ptr)
          if (fabs(*ptr) > thresh)
            cout << setw(3) << n << setw(3) << m << setw(3) << l << setw(3)
                 << k << setw(3) << j << setw(3) << i
                 << setw(20) << setprecision(7) << *ptr << endl;
}
