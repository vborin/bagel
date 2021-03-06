//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: properties.h
// Copyright (C) 2013 Toru Shiozaki
//
// Author: Shane Parker <shane.parker@u.northwestern.edu>
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



#ifndef __BAGEL_FCI_PROPERTIES_H
#define __BAGEL_FCI_PROPERTIES_H

#include <src/wfn/reference.h>
#include <src/scf/hf/rhf.h>
#include <src/ci/fci/dvec.h>

namespace bagel {

class CIProperties {
  protected:
    int nocc_;
    int norb_;
    int nbasis_;
    int sizeij_;

    double core_prop_;

    std::shared_ptr<const Matrix> prop_;
    std::shared_ptr<const Geometry> geom_;
    std::shared_ptr<const Reference> ref_;
    std::shared_ptr<const Coeff> coeff_;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
      ar & nocc_ & norb_ & nbasis_ & sizeij_ & core_prop_ & prop_ & geom_ & ref_ & coeff_;
    }

  public:
    CIProperties() { }
    CIProperties(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence)
      : nocc_(nstart), norb_(nfence-nstart), nbasis_(ref->geom()->nbasis()), geom_(ref->geom()), ref_(ref), coeff_(ref->coeff()) { }
    CIProperties(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence, const std::shared_ptr<const Coeff> coeff)
      : nocc_(nstart), norb_(nfence-nstart), nbasis_(ref->geom()->nbasis()), geom_(ref->geom()), ref_(ref), coeff_(coeff) { }
    virtual ~CIProperties() { }

    virtual void compute(std::shared_ptr<const Dvec>) = 0;

    const std::shared_ptr<const Geometry> geom() const { return geom_; };
    const std::shared_ptr<const Matrix> prop() const { return prop_; };

    virtual double core() const { return core_prop_; };
    virtual void print() const = 0;

  private:
    virtual void init(const int nstart, const int nfence) = 0; // init should do everything it can that does not require the Civecs
};

// 1e properties of a CI wavefunction : This is kind of useless right now, but I envision it being less useless when there are more properties to calculate
// It just so happens that the only property I'm calculating at the moment is a special case (with 3 components)
class Prop1e : public CIProperties {
  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
      ar & boost::serialization::base_object<CIProperties>(*this);
    }
  public:
    Prop1e() { }
    Prop1e(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence) : CIProperties(ref, nstart, nfence) {}
    Prop1e(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence, const std::shared_ptr<const Coeff> coeff)
      : CIProperties(ref,nstart,nfence, coeff) {}
    virtual ~Prop1e() { }
};

// Dipole operator of a CI wavefunction
class CIDipole : public Prop1e {
  protected:
    std::array<std::shared_ptr<const Matrix>, 3> dipole_mo_;
    std::array<std::shared_ptr<Matrix>, 3> dipole_matrices_;
    std::array<double,3> core_dipole_;
    std::array<std::shared_ptr<Matrix>, 3> compressed_dipoles_;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
      ar & boost::serialization::base_object<Prop1e>(*this) & dipole_mo_ & dipole_matrices_ & core_dipole_ & compressed_dipoles_;
    }

  public:
    CIDipole() { }
    CIDipole(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence) : Prop1e(ref, nstart, nfence)
      { init(nstart,nfence); }
    CIDipole(const std::shared_ptr<const Reference> ref, const int nstart, const int nfence, const std::shared_ptr<const Coeff> coeff)
      : Prop1e(ref, nstart, nfence, coeff) { init(nstart, nfence); }

    void init(const int nstart, const int nfence) override;
    virtual void compute(std::shared_ptr<const Dvec> ccvec) override;

    std::array<double,3> core_dipole() const { return core_dipole_; }
    double core_dipole(const int i) const { return core_dipole_[i]; }
    std::array<std::shared_ptr<Matrix>, 3> dipoles() const { return dipole_matrices_; }
    std::shared_ptr<Matrix> dipoles(const int i) const { return dipole_matrices_[i]; }

    virtual void print() const override;
};

}

#include <src/util/archive.h>
BOOST_CLASS_EXPORT_KEY(bagel::CIProperties)
BOOST_CLASS_EXPORT_KEY(bagel::Prop1e)
BOOST_CLASS_EXPORT_KEY(bagel::CIDipole)
namespace bagel {
  template <class T>
  struct base_of<T, typename std::enable_if<std::is_base_of<CIProperties, T>::value>::type> {
    typedef CIProperties type;
  };
}

#endif
