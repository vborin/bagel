//
// Author : Toru Shiozaki
// Date   : Dec 2011
//

#ifndef __NEWINT_FCI_RDM_H
#define __NEWINT_FCI_RDM_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <src/util/f77.h>

template <int rank>
class RDM {
  protected:
    std::unique_ptr<double[]> data_;
    const int norb_;
    int dim_;

  public:
    RDM(const int n) : norb_(n) {
      assert(rank > 0);
      dim_ = 1;
      for (int i = 0; i != rank; ++i) dim_ *= n;
      std::unique_ptr<double[]> data__(new double[dim_*dim_]);
      data_ = std::move(data__);
    };
    RDM(const RDM& o) : norb_(o.norb_), dim_(o.dim_) {
      std::unique_ptr<double[]> data__(new double[dim_*dim_]);
      data_ = std::move(data__);
      std::copy(o.data(), o.data()+dim_*dim_, data());
    };
    ~RDM() {  };

    double* data() { return data_.get(); };
    const double* data() const { return data_.get(); };
    double* first() { return data(); };
    double& element(int i, int j) { return data_[i+j*dim_]; };
    const double& element(int i, int j) const { return data_[i+j*dim_]; };
    const double* element_ptr(int i, int j) const { return &element(i,j); };
    // careful, this should not be called for those except for 2RDM.
    double& element(int i, int j, int k, int l) { assert(rank == 2); return data_[i+norb_*(j+norb_*(k+norb_*l))]; };
    double* element_ptr(int i, int j, int k, int l) { assert(rank == 2); return &element(i,j,k,l); };
    const double& element(int i, int j, int k, int l) const { assert(rank == 2); return data_[i+norb_*(j+norb_*(k+norb_*l))]; };

    void zero() { std::fill(data(), data()+dim_*dim_, 0.0); };
    void daxpy(const double a, const RDM& o) {
      daxpy_(dim_*dim_, a, o.data(), 1, data(), 1);
    };

    void daxpy(const double a, const std::shared_ptr<RDM>& o) { this->daxpy(a, *o); };

    std::vector<double> diag() const {
      std::vector<double> out(dim_);
      for (int i = 0; i != dim_; ++i) out[i] = element(i,i);
      return out;
    };

    std::pair<std::vector<double>, std::vector<double> > generate_natural_orbitals() const {
      assert(rank == 1);
      std::vector<double> buf(dim_*dim_);
      std::vector<double> vec(dim_);
#define ALIGN
#ifdef ALIGN
      for (int i = 0; i != dim_; ++i) buf[i+i*dim_] = 2.0; 
      daxpy_(dim_*dim_, -1.0, data(), 1, &(buf[0]), 1);
#else
      daxpy_(dim_*dim_, 1.0, data(), 1, &(buf[0]), 1);
#endif
      int lwork = 5*dim_;
      std::unique_ptr<double[]> work(new double[lwork]);
      int info;
      dsyev_("V", "U", &dim_, &(buf[0]), &dim_, &(vec[0]), work.get(), &lwork, &info);
      assert(!info);
#ifdef ALIGN
      for (auto i = vec.begin(); i != vec.end(); ++i) *i = 2.0-*i;
#endif
      return std::make_pair(buf, vec);
    };

    void transform(const std::vector<double>& coeff) {
      const double* start = &(coeff[0]);
      std::unique_ptr<double[]> buf(new double[dim_*dim_]);
      if (rank == 1) {
        dgemm_("N", "N", dim_, dim_, dim_, 1.0, data(), dim_, start, dim_, 0.0, buf.get(), dim_); 
        dgemm_("T", "N", dim_, dim_, dim_, 1.0, start, dim_, buf.get(), dim_, 0.0, data(), dim_); 
      } else if (rank == 2) {
        // first half transformation
        dgemm_("N", "N", dim_*norb_, norb_, norb_, 1.0, data(), dim_*norb_, start, norb_, 0.0, buf.get(), dim_*norb_); 
        for (int i = 0; i != norb_; ++i)
          dgemm_("N", "N", dim_, norb_, norb_, 1.0, buf.get()+i*dim_*norb_, dim_, start, norb_, 0.0, data()+i*dim_*norb_, dim_); 
        // then tranpose
        mytranspose_(data(), &dim_, &dim_, buf.get());
        // and do it again
        dgemm_("N", "N", dim_*norb_, norb_, norb_, 1.0, buf.get(), dim_*norb_, start, norb_, 0.0, data(), dim_*norb_); 
        for (int i = 0; i != norb_; ++i)
          dgemm_("N", "N", dim_, norb_, norb_, 1.0, data()+i*dim_*norb_, dim_, start, norb_, 0.0, buf.get()+i*dim_*norb_, dim_);
        // to make sure for non-symmetric density matrices (and anyway this should be cheap).
        mytranspose_(buf.get(), &dim_, &dim_, data());
      } else {
        assert(false);
      }
    };

    void print() {
      if (rank == 1) {
        for (int i = 0; i != norb_; ++i) {
          for (int j = 0; j != norb_; ++j)
            std::cout << std::setw(12) << std::setprecision(7) << element(j,i); 
          std::cout << std::endl;
        }
      } else if (rank == 2) {
        for (int i = 0; i != norb_; ++i) {
          for (int j = 0; j != norb_; ++j) {
            for (int k = 0; k != norb_; ++k) {
              for (int l = 0; l != norb_; ++l) {
                if (std::abs(element(l,k,j,i)) > 1.0e-0) std::cout << std::setw(3) << l << std::setw(3)
                      << k << std::setw(3) << j << std::setw(3) << i
                      << std::setw(12) << std::setprecision(7) << element(l,k,j,i) << std::endl;
        } } } }
      }
    };
};

#endif
