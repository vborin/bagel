//
// Newint - Parallel electron correlation program.
// Filename: df.h
// Copyright (C) 2012 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the Newint package (to be renamed).
//
// The Newint package is free software; you can redistribute it and\/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// The Newint package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the Newint package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//


#ifndef __NEWINT_DF_DensityFit_H
#define __NEWINT_DF_DensityFit_H

#include <vector>
#include <memory>
#include <src/scf/atom.h>
#include <src/util/f77.h>
#include <src/rysint/eribatch.h>
#include <stdexcept>

class DF_Half;
class DF_Full;


class DensityFit : public std::enable_shared_from_this<DensityFit> {
  protected:
    // #orbital basis
    const size_t nbasis0_;
    const size_t nbasis1_;
    // #auxiliary basis
    const size_t naux_;
    // AO three-index integrals (naux, nbasis1, nbasis0);
    std::unique_ptr<double[]> data_;
    // AO two-index integrals ^ -1/2
    std::unique_ptr<double[]> data2_;

    // returns three-index integrals
    double* data() { return data_.get(); };
    // returns two-index integrals ^-1/2
    double* data2() { return data2_.get(); };
    const double* const data() const { return data_.get(); };
    const double*  const data2() const { return data2_.get(); };

    void common_init(const std::vector<std::shared_ptr<Atom> >&, const std::vector<std::vector<int> >&,
                     const std::vector<std::shared_ptr<Atom> >&, const std::vector<std::vector<int> >&,
                     const std::vector<std::shared_ptr<Atom> >&, const std::vector<std::vector<int> >&, const double, const bool);

    // returns a pointer to a stack memory area
    virtual const double* compute_batch(std::vector<std::shared_ptr<Shell> >&) = 0;

    size_t size() const { return nbasis0_*nbasis1_*naux_; };

  public:
    DensityFit(const int nbas, const int naux) : nbasis0_(nbas), nbasis1_(nbas), naux_(naux) {};
    DensityFit(const int nbas0, const int nbas1, const int naux) : nbasis0_(nbas0), nbasis1_(nbas1), naux_(naux) {};
    ~DensityFit() {};

    const double* const data_3index() const { return data(); };
    const double* const data_2index() const { return data2(); };

    size_t nbasis0() const { return nbasis0_; };
    size_t nbasis1() const { return nbasis1_; };
    size_t naux() const { return naux_; };

    // compute half transforms; c is dimensioned by nbasis_;
    std::shared_ptr<DF_Half> compute_half_transform(const double* c, const size_t nocc) const;

};


class DF_AO : public DensityFit {
  protected:
    const double* compute_batch(std::vector<std::shared_ptr<Shell> >& input) {
      throw std::logic_error("DF_AO::compute_batch should not be called");
    };
  public:
    DF_AO(const int nbas0, const int nbas1, const int naux, std::unique_ptr<double[]>& dat) : DensityFit(nbas0, nbas1, naux) {
      data_ = std::move(dat); 
    };
    ~DF_AO() {};

};


class DF_Half {

  protected:
    const std::shared_ptr<const DensityFit> df_;
    const size_t nocc_;

    std::unique_ptr<double[]> data_;
    const size_t nbasis_;
    const size_t naux_;

    size_t size() const { return naux_*nbasis_*nocc_; };

  public:
    DF_Half(const std::shared_ptr<const DensityFit> df, const int nocc, std::unique_ptr<double[]>& in)
     : df_(df), nocc_(nocc), data_(std::move(in)), nbasis_(df->nbasis0()), naux_(df->naux()) {};

    ~DF_Half() {};

    double* const data() { return data_.get(); };
    const double* const data() const { return data_.get(); };
    std::unique_ptr<double[]> move_data() { return std::move(data_); };

    std::shared_ptr<DF_Half> clone() const;
    std::shared_ptr<DF_Half> copy() const;

    std::shared_ptr<DF_Half> apply_J() const { return apply_J(df_); };
    std::shared_ptr<DF_Half> apply_J(std::shared_ptr<const DensityFit> d) const;

    std::shared_ptr<DF_Full> compute_second_transform(const double* c, const size_t nocc) const;

    void form_2index(std::unique_ptr<double[]>& target, const double a = 1.0, const double b = 0.0) const;
    void form_2index(std::unique_ptr<double[]>& target, std::shared_ptr<const DF_Full> o, const double a = 1.0, const double b = 0.0) const;

    // form K operator
    std::unique_ptr<double[]> form_4index() const;
    void form_4index(std::unique_ptr<double[]>& target) const;

    // AO back transformation
    std::shared_ptr<DF_AO> back_transform(const double*) const;

};


class DF_Full {

  protected:
    const std::shared_ptr<const DensityFit> df_;
    const size_t nocc1_; // inner
    const size_t nocc2_; // outer

    std::unique_ptr<double[]> data_;
    const size_t naux_;

    size_t size() const { return nocc1_*nocc2_*naux_; };

  public:
    DF_Full(const std::shared_ptr<const DensityFit> df, const size_t nocc1, const size_t nocc2, std::unique_ptr<double[]>& in)
      : df_(df), nocc1_(nocc1), nocc2_(nocc2), data_(std::move(in)), naux_(df->naux()) {};

    ~DF_Full() {};

    const int nocc1() const { return nocc1_; };
    const int nocc2() const { return nocc2_; };

    std::shared_ptr<DF_Full> apply_J() const { return apply_J(df_); };
    std::shared_ptr<DF_Full> apply_J(std::shared_ptr<const DensityFit> d) const;

    std::shared_ptr<DF_Full> apply_2rdm(const double* rdm) const;
    std::shared_ptr<DF_Full> apply_closed_2RDM() const;

    // forming all internal 4-index MO integrals
    void form_4index(std::unique_ptr<double[]>& target) const;
    std::unique_ptr<double[]> form_4index() const;
    void form_4index(std::unique_ptr<double[]>& target, const std::shared_ptr<const DF_Full> o) const;
    std::unique_ptr<double[]> form_4index(const std::shared_ptr<const DF_Full> o) const;

    // the same as above, but with one index fixed at n (of nocc2).
    void form_4index(std::unique_ptr<double[]>& target, const std::shared_ptr<const DF_Full> o, const size_t n) const;
    std::unique_ptr<double[]> form_4index(const std::shared_ptr<const DF_Full> o, const size_t n) const;

    // forming two-external K operators
    void form_4index(std::unique_ptr<double[]>& target, const std::shared_ptr<const DensityFit> o) const;
    std::unique_ptr<double[]> form_4index(const std::shared_ptr<const DensityFit> o) const;

    double* data() { return data_.get(); };
    const double* const data() const { return data_.get(); };
    const std::shared_ptr<const DensityFit> df() const { return df_; };

    std::shared_ptr<DF_Full> copy() const;

    // AO back transformation for gradient evaluations
    std::shared_ptr<DF_Half> back_transform(const double* c) const;

};

#endif

