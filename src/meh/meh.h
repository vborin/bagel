//
// BAGEL - Parallel electron correlation program.
// Filename: meh.h
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

#ifndef __MEH_MEH_H
#define __MEH_MEH_H

#include <src/dimer/dimer.h>
#include <src/dimer/dimer_jop.h>
#include <src/dimer/dimer_prop.h>
#include <src/math/davidson.h>
#include <src/meh/gamma_forest.h>
#include <src/meh/meh_base.h>
#include <src/smith/prim_op.h>

namespace bagel {

// forward declaration
template <class VecType>
class MultiExcitonHamiltonian;

namespace asd {
// implementation class. true = Hamiltonian, false = RDM.
template <bool _N>
struct ASD_impl {
  template<typename T>
  using DSb = DimerSubspace_base<T>;
  using return_type = std::shared_ptr<typename std::conditional<_N, Matrix, RDM<2>>::type>;
  template <class VecType> static return_type compute_diagonal_block(MultiExcitonHamiltonian<VecType>*, DSb<VecType>& subspace)         { assert(false); return nullptr; }
  template <class VecType> static return_type compute_inter_2e(MultiExcitonHamiltonian<VecType>*, DSb<VecType>& AB, DSb<VecType>& ApBp) { assert(false); return nullptr; }
};
}

/// Template for MEH (to be renamed ASD)
template <class VecType>
class MultiExcitonHamiltonian : public MEH_base {
  protected: using DSubSpace = DimerSubspace_base<VecType>;
  protected: using DCISpace = DimerCISpace_base<VecType>;
  protected: using CiType = typename VecType::Ci;

  template <bool>
  friend class asd::ASD_impl;

  protected:
    std::shared_ptr<DCISpace> cispace_;
    std::shared_ptr<GammaForest<VecType, 2>> gammaforest_;
    std::vector<DSubSpace> subspaces_;

    void modelize();

  public:
    MultiExcitonHamiltonian(const std::shared_ptr<const PTree> input, std::shared_ptr<Dimer> dimer, std::shared_ptr<DCISpace> cispace);

    void compute() override;
    void compute_rdm() const override;

    void print_hamiltonian(const std::string title = "MultiExciton Hamiltonian", const int nstates = 10) const;
    void print_states(const Matrix& cc, const std::vector<double>& energies, const double thresh = 0.01, const std::string title = "Adiabats") const;
    void print_property(const std::string label, std::shared_ptr<const Matrix>, const int size = 10) const ;
    void print(const double thresh = 0.01) const;

  private:
    const Coupling coupling_type(const DSubSpace& AB, const DSubSpace& ApBp) const;

    void generate_initial_guess(std::shared_ptr<Matrix> cc, std::vector<DSubSpace>& subspace, const int nstates);
    std::shared_ptr<Matrix> apply_hamiltonian(const Matrix& o, std::vector<DSubSpace>& subspaces);
    std::vector<double> diagonalize(std::shared_ptr<Matrix>& cc, std::vector<DSubSpace>& subspace, const bool mute = false);

    std::shared_ptr<Matrix> compute_1e_prop(std::shared_ptr<const Matrix> hAA, std::shared_ptr<const Matrix> hBB, std::shared_ptr<const Matrix> hAB, const double core) const;
    std::shared_ptr<Matrix> compute_offdiagonal_1e(const DSubSpace& AB, const DSubSpace& ApBp, std::shared_ptr<const Matrix> hAB) const;
    std::shared_ptr<Matrix> compute_diagonal_1e(const DSubSpace& subspace, const double* hAA, const double* hBB, const double diag) const;

    // Diagonal block stuff
    void compute_pure_terms(DSubSpace& subspace, std::shared_ptr<const DimerJop> jop);
    std::shared_ptr<Matrix> compute_intra(const DSubSpace& subspace, std::shared_ptr<const DimerJop> jop, const double diag);

    virtual std::shared_ptr<VecType> form_sigma(std::shared_ptr<const VecType> ccvec, std::shared_ptr<const MOFile> jop) const = 0;
    virtual std::shared_ptr<VecType> form_sigma_1e(std::shared_ptr<const VecType> ccvec, const double* modata) const = 0;

    // Gamma Tree building
    void gamma_couple_blocks(DSubSpace& AB, DSubSpace& ApBp, std::shared_ptr<GammaForest<VecType,2>> gammaforest);
    void spin_couple_blocks(DSubSpace& AB, DSubSpace& ApBp, std::map<std::pair<int, int>, double>& spinmap); // Off-diagonal driver for S^2
    void compute_diagonal_spin_block(DSubSpace& subspace, std::map<std::pair<int, int>, double>& spinmap);

    // Off-diagonal stuff
    template <bool _N, typename return_type = typename std::conditional<_N, Matrix, RDM<2>>::type>
    std::shared_ptr<return_type> couple_blocks(DSubSpace& AB, DSubSpace& ApBp); // Off-diagonal driver for H

    template <bool _N> auto compute_diagonal_block(DSubSpace& subspace)      -> typename asd::ASD_impl<_N>::return_type { return asd::ASD_impl<_N>::compute_diagonal_block(this, subspace); }
    template <bool _N> auto compute_inter_2e(DSubSpace& AB, DSubSpace& ApBp) -> typename asd::ASD_impl<_N>::return_type { return asd::ASD_impl<_N>::compute_inter_2e(this, AB, ApBp); }
};

// Locks to make sure the following files are not included on their own
#define MEH_HEADERS
#include <src/meh/meh_compute.hpp>
#include <src/meh/meh_compute_diagonal.hpp>
#include <src/meh/meh_compute_offdiagonal.hpp>
#include <src/meh/meh_gamma_coupling.hpp>
#include <src/meh/meh_init.hpp>
#include <src/meh/meh_modelize.hpp>
#include <src/meh/meh_diagonalize.hpp>
#include <src/meh/meh_spin_coupling.hpp>
#include <src/meh/meh_compute_rdm.hpp>
#include <src/meh/asd_impl.hpp>
#undef MEH_HEADERS

}

#endif
