//
// BAGEL - Parallel electron correlation program.
// Filename: box.h
// Copyright (C) 2016 Toru Shiozaki
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


#ifndef __SRC_PERIODIC_BOX_H
#define __SRC_PERIODIC_BOX_H

#include <src/util/constants.h>
#include <src/molecule/shellpair.h>

namespace bagel {

class Box {
  friend class FMM;
  protected:
    int boxid_, lmax_;
    std::array<int, 3> tvec_;
    std::array<double, 3> centre_;
    double boxsize_;
    std::shared_ptr<const Box> parent_;
    std::vector<std::weak_ptr<const Box>> child_;
    std::vector<std::shared_ptr<const Box>> inter_;
    std::vector<std::shared_ptr<const Box>> neigh_;
    std::vector<std::shared_ptr<const ShellPair>> sp_;

    bool is_leaf_;
    double thresh_, extent_;
    int nsp_, nchild_, nneigh_, ninter_, nbasis0_, nbasis1_;


    void init();
    void insert_sp(std::vector<std::shared_ptr<const ShellPair>>);
    void get_parent(std::shared_ptr<const Box> = NULL);
    void insert_child(std::shared_ptr<const Box> = NULL);
    bool is_neigh(std::shared_ptr<const Box> b, const int ws);
    void insert_neigh(std::shared_ptr<const Box> b, const bool is_neigh = false, const int ws = 2);

    std::vector<std::shared_ptr<const ZMatrix>> multipole_;
    std::vector<std::shared_ptr<const ZMatrix>> local_expansion_; // size = ninter_
    void compute_multipoles();
    void compute_local_expansions(std::shared_ptr<const Matrix> density);
    std::shared_ptr<const ZMatrix> compute_node_energy(const int dim, std::shared_ptr<const Matrix> density, std::vector<double> max_den, const bool dodf = false, const double schwarz_thresh = 0.0);


  public:
    Box(int id, std::array<int, 3> v, const int lmax = 10, std::vector<std::shared_ptr<const ShellPair>> sp = std::vector<std::shared_ptr<const ShellPair>>()) : boxid_(id), lmax_(lmax), tvec_(v), sp_(sp) { }
    ~Box() { }

    std::array<double, 3> centre() const { return centre_; }
    double centre(const int i) const { return centre_[i]; }

    int nsp() const { return nsp_; }
    int nchild() const { return nchild_; }
    int nneigh() const { return nneigh_; }
    int ninter() const { return ninter_; }
    bool is_leaf() const { return is_leaf_; }
    double extent() const { return extent_; }
    int nbasis0() const { return nbasis0_; }
    int nbasis1() const { return nbasis1_; }

    std::shared_ptr<const Box> parent() const { return parent_; }
    std::shared_ptr<const Box> child(const int i) const { return child_[i].lock(); }
    std::vector<std::shared_ptr<const Box>> neigh() const { return neigh_; }
    std::vector<std::shared_ptr<const Box>> interaction_list() const { return inter_; }
    std::vector<std::shared_ptr<const ShellPair>> sp() const { return sp_; }
    std::shared_ptr<const ShellPair> sp(const int i) const { return sp_[i]; }
    std::array<std::shared_ptr<const Shell>, 2> shells(const int i) const { return sp_[i]->shells(); }

    std::vector<std::shared_ptr<const ZMatrix>> multipole() const { return multipole_; }
    std::shared_ptr<const ZMatrix> multipole(const int i) const { return multipole_[i]; }
    std::vector<std::shared_ptr<const ZMatrix>> local_expansion() const { return local_expansion_; }
    std::shared_ptr<const ZMatrix> local_expansion(const int i) const { return local_expansion_[i]; }

    void print_node() const;
};

}
#endif
