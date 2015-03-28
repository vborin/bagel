//
// BAGEL - Parallel electron correlation program.
// Filename: CASPT2_gen11.cc
// Copyright (C) 2014 Shiozaki group
//
// Author: Shiozaki group <shiozaki@northwestern.edu>
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH

#include <src/smith/CASPT2_tasks11.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CASPT2;

Task500::Task500(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[2]->nblock()*range[1]->nblock());
  for (auto& a2 : *range[2])
    for (auto& x3 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x3, a2}}, in, t[0], range));
}

Task501::Task501(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[1]->nblock());
  for (auto& a2 : *range[2])
    for (auto& x3 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x3, a2}}, in, t[0], range));
}

Task502::Task502(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[1]->nblock()*range[0]->nblock());
  for (auto& x4 : *range[1])
    for (auto& x3 : *range[1])
      for (auto& x5 : *range[1])
        for (auto& c1 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c1, x5, x3, x4}}, in, t[0], range));
}

Task503::Task503(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& x0 : *range[1])
    for (auto& x1 : *range[1])
      for (auto& c1 : *range[0])
        for (auto& x2 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x2, c1, x1, x0}}, in, t[0], range));
}

Task504::Task504(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[1]->nblock());
  for (auto& a2 : *range[2])
    for (auto& x3 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x3, a2}}, in, t[0], range));
}

Task505::Task505(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[1]->nblock()*range[0]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x4 : *range[1])
      for (auto& x5 : *range[1])
        for (auto& c1 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c1, x5, x4, x3}}, in, t[0], range));
}

Task506::Task506(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& x0 : *range[1])
    for (auto& x1 : *range[1])
      for (auto& c1 : *range[0])
        for (auto& x2 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x2, c1, x1, x0}}, in, t[0], range));
}

Task507::Task507(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[1]->nblock());
  for (auto& a2 : *range[2])
    for (auto& x3 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x3, a2}}, in, t[0], range));
}

Task508::Task508(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[1]->nblock()*range[2]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x4 : *range[1])
      for (auto& x5 : *range[1])
        for (auto& a1 : *range[2])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{a1, x5, x4, x3}}, in, t[0], range));
}

Task509::Task509(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[2]->nblock()*range[1]->nblock()*range[1]->nblock());
  for (auto& x0 : *range[1])
    for (auto& a1 : *range[2])
      for (auto& x1 : *range[1])
        for (auto& x2 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x2, x1, a1, x0}}, in, t[0], range));
}

Task510::Task510(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[2]->nblock());
  for (auto& x1 : *range[1])
    for (auto& a2 : *range[2])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{a2, x1}}, in, t[0], range));
}

Task511::Task511(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[1]->nblock());
  for (auto& a2 : *range[2])
    for (auto& x1 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x1, a2}}, in, t[0], range));
}

Task512::Task512(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock()*range[0]->nblock()*range[0]->nblock());
  for (auto& x0 : *range[1])
    for (auto& x1 : *range[1])
      for (auto& c3 : *range[0])
        for (auto& c1 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c1, c3, x1, x0}}, in, t[0], range));
}

Task513::Task513(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[1]->nblock()*range[0]->nblock());
  for (auto& x2 : *range[1])
    for (auto& c3 : *range[0])
      for (auto& x3 : *range[1])
        for (auto& c1 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c1, x3, c3, x2}}, in, t[0], range));
}

Task514::Task514(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{a2, c1}}, in, t[0], range));
}

Task515::Task515(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{a2, c1}}, in, t[0], range));
}

Task516::Task516(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock());
  for (auto& x0 : *range[1])
    for (auto& c3 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c3, x0}}, in, t[0], range));
}

Task517::Task517(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[1]->nblock()*range[1]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c3 : *range[0])
      for (auto& x2 : *range[1])
        for (auto& x3 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x3, x2, c3, x1}}, in, t[0], range));
}

Task518::Task518(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock());
  for (auto& c3 : *range[0])
    for (auto& a2 : *range[2])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{a2, c3}}, in, t[0], range));
}

Task519::Task519(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[0]->nblock());
  for (auto& a2 : *range[2])
    for (auto& c3 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c3, a2}}, in, t[0], range));
}

Task520::Task520(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock());
  for (auto& x0 : *range[1])
    for (auto& c1 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c1, x0}}, in, t[0], range));
}

Task521::Task521(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[1]->nblock()*range[1]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& x2 : *range[1])
        for (auto& x3 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x3, x2, c1, x1}}, in, t[0], range));
}

Task522::Task522(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[2]->nblock()*range[0]->nblock());
  for (auto& a2 : *range[2])
    for (auto& c3 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c3, a2}}, in, t[0], range));
}

Task523::Task523(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a4 : *range[2])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{a4, c1}}, in, t[0], range));
}

Task524::Task524(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[2]->nblock()*range[1]->nblock());
  for (auto& x0 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& a4 : *range[2])
        for (auto& x1 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x1, a4, c1, x0}}, in, t[0], range));
}

Task525::Task525(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x2 : *range[1])
    for (auto& x1 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x1, x2}}, in, t[0], range));
}

Task526::Task526(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x1 : *range[1])
    for (auto& x2 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x2, x1}}, in, t[0], range));
}

Task527::Task527(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x0 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x0, x3}}, in, t[0], range));
}

Task528::Task528(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

Task529::Task529(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x0 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x0, x3}}, in, t[0], range));
}

Task530::Task530(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

Task531::Task531(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x1 : *range[1])
    for (auto& x2 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x2, x1}}, in, t[0], range));
}

Task532::Task532(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x0 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x0, x3}}, in, t[0], range));
}

Task533::Task533(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[2]->nblock()*range[0]->nblock()*range[2]->nblock());
  for (auto& x0 : *range[1])
    for (auto& a1 : *range[2])
      for (auto& c2 : *range[0])
        for (auto& a3 : *range[2])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{a3, c2, a1, x0}}, in, t[0], range));
}

Task534::Task534(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[1]->nblock());
  for (auto& x3 : *range[1])
    for (auto& x0 : *range[1])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{x0, x3}}, in, t[0], range));
}

Task535::Task535(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[1]->nblock()*range[2]->nblock()*range[0]->nblock()*range[2]->nblock());
  for (auto& x0 : *range[1])
    for (auto& a1 : *range[2])
      for (auto& c2 : *range[0])
        for (auto& a3 : *range[2])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{a3, c2, a1, x0}}, in, t[0], range));
}

Task536::Task536(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c1 : *range[0])
    for (auto& c4 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c4, c1}}, in, t[0], range));
}

Task537::Task537(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c4 : *range[0])
    for (auto& c1 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c1, c4}}, in, t[0], range));
}

Task538::Task538(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[2]->nblock()*range[0]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& a2 : *range[2])
        for (auto& c3 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c3, a2, c1, x1}}, in, t[0], range));
}

Task539::Task539(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

Task540::Task540(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c4 : *range[0])
    for (auto& c1 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c1, c4}}, in, t[0], range));
}

Task541::Task541(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[2]->nblock()*range[0]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& a2 : *range[2])
        for (auto& c3 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c3, a2, c1, x1}}, in, t[0], range));
}

Task542::Task542(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

Task543::Task543(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c3 : *range[0])
    for (auto& c4 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c4, c3}}, in, t[0], range));
}

Task544::Task544(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c4 : *range[0])
    for (auto& c3 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c3, c4}}, in, t[0], range));
}

Task545::Task545(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[2]->nblock()*range[0]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& a2 : *range[2])
        for (auto& c3 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c3, a2, c1, x1}}, in, t[0], range));
}

Task546::Task546(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

Task547::Task547(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[0]->nblock()*range[0]->nblock());
  for (auto& c4 : *range[0])
    for (auto& c3 : *range[0])
      subtasks_.push_back(make_shared<Task_local>(array<const Index,2>{{c3, c4}}, in, t[0], range));
}

Task548::Task548(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,2> in = {{t[1], t[2]}};
  subtasks_.reserve(range[1]->nblock()*range[0]->nblock()*range[2]->nblock()*range[0]->nblock());
  for (auto& x1 : *range[1])
    for (auto& c1 : *range[0])
      for (auto& a2 : *range[2])
        for (auto& c3 : *range[0])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{c3, a2, c1, x1}}, in, t[0], range));
}

Task549::Task549(vector<shared_ptr<Tensor>> t, array<shared_ptr<const IndexRange>,3> range) {
  array<shared_ptr<const Tensor>,1> in = {{t[1]}};
  subtasks_.reserve(range[0]->nblock()*range[2]->nblock()*range[0]->nblock()*range[1]->nblock());
  for (auto& c1 : *range[0])
    for (auto& a2 : *range[2])
      for (auto& c3 : *range[0])
        for (auto& x0 : *range[1])
          subtasks_.push_back(make_shared<Task_local>(array<const Index,4>{{x0, c3, a2, c1}}, in, t[0], range));
}

#endif
