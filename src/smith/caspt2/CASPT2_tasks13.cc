//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: CASPT2_tasks13.cc
// Copyright (C) 2014 Toru Shiozaki
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

#include <bagel_config.h>
#ifdef COMPILE_SMITH

#include <src/smith/caspt2/CASPT2_tasks13.h>

using namespace std;
using namespace bagel;
using namespace bagel::SMITH;
using namespace bagel::SMITH::CASPT2;

void Task600::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  // tensor label: I732
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
      sort_indices<0,1,2,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
      dgemm_("T", "N", 1, x0.size()*c3.size(), a2.size()*c1.size(),
             1.0, i0data_sorted, a2.size()*c1.size(), i1data_sorted, a2.size()*c1.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c3.size(), x0.size());
  out()->add_block(odata, x0, c3);
}

void Task601::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, c1, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, c1, x1)]);
    sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), c1.size(), x1.size());
    // tensor label: I736
    std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c1)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), c1.size());
    dgemm_("T", "N", x3.size()*x2.size()*x1.size(), x0.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, x3.size()*x2.size()*x1.size());
  }
  sort_indices<3,0,1,2,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x1.size(), x0.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task602::Task_local::compute() {
  const Index x0 = b(0);
  const Index c1 = b(1);
  // tensor label: I736
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c1)]);
  std::fill_n(odata.get(), out()->get_size(x0, c1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: f1
      std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2)]);
      sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
      sort_indices<2,1,0,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
      dgemm_("T", "N", 1, x0.size()*c1.size(), c3.size()*a2.size(),
             1.0, i0data_sorted, c3.size()*a2.size(), i1data_sorted, c3.size()*a2.size(),
             1.0, odata_sorted, 1);
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, c1.size(), x0.size());
  out()->add_block(odata, x0, c1);
}

void Task603::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& a2 : *range_[2]) {
    for (auto& c1 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a2, c1, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a2, c1, x2)]);
      sort_indices<1,2,0,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a2.size(), c1.size(), x2.size());
      // tensor label: I774
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a2, c1, x1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a2, c1, x1)]);
      sort_indices<1,2,0,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), a2.size(), c1.size(), x1.size());
      dgemm_("T", "N", x3.size()*x2.size(), x0.size()*x1.size(), a2.size()*c1.size(),
             1.0, i0data_sorted, a2.size()*c1.size(), i1data_sorted, a2.size()*c1.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,0,1,3,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x0.size(), x1.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task604::Task_local::compute() {
  const Index x0 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I774
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a2, c1, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<2,0,1,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), x0.size()*a2.size()*c1.size(), c3.size(),
           1.0, i0data_sorted, c3.size(), i1data_sorted, c3.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), x0.size());
  out()->add_block(odata, x0, a2, c1, x1);
}

void Task605::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, x3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2, x3, x2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), x3.size(), x2.size());
      // tensor label: I778
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, a2, x1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, a2, x1)]);
      sort_indices<1,2,0,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), a2.size(), x1.size());
      dgemm_("T", "N", x3.size()*x2.size(), x0.size()*x1.size(), c3.size()*a2.size(),
             1.0, i0data_sorted, c3.size()*a2.size(), i1data_sorted, c3.size()*a2.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,0,1,3,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x0.size(), x1.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task606::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index x1 = b(3);
  // tensor label: I778
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, a2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, a2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, a2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, a2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<0,1,2,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), x0.size()*c3.size()*a2.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), a2.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, a2, x1);
}

void Task607::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, x3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, x3, x2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), x3.size(), x2.size());
      // tensor label: I782
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a2, c1, x1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a2, c1, x1)]);
      sort_indices<2,1,0,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), a2.size(), c1.size(), x1.size());
      dgemm_("T", "N", x3.size()*x2.size(), x0.size()*x1.size(), a2.size()*c1.size(),
             1.0, i0data_sorted, a2.size()*c1.size(), i1data_sorted, a2.size()*c1.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,0,1,3,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x0.size(), x1.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task608::Task_local::compute() {
  const Index x0 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I782
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, a2, c1, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a2, c1, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a2, c1, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<2,0,1,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), x0.size()*a2.size()*c1.size(), c3.size(),
           1.0, i0data_sorted, c3.size(), i1data_sorted, c3.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), c1.size(), a2.size(), x0.size());
  out()->add_block(odata, x0, a2, c1, x1);
}

void Task609::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      // tensor label: v2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, x1, a2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, x1, a2)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), x1.size(), a2.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, x3, x2)]);
      sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c1.size(), a2.size(), x3.size(), x2.size());
      dgemm_("T", "N", x0.size()*x1.size(), x2.size()*x3.size(), a2.size()*c1.size(),
             1.0, i0data_sorted, a2.size()*c1.size(), i1data_sorted, a2.size()*c1.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<0,2,3,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), x3.size(), x2.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task610::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I731
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x3, x2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x3, x2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: h1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(x3, x2, c1, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, x2, c1, x1)]);
    sort_indices<2,0,1,3,0,1,2,1>(i1data, i1data_sorted, x3.size(), x2.size(), c1.size(), x1.size());
    dgemm_("T", "N", x0.size(), x1.size()*x2.size()*x3.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, x0.size(), x3.size(), x2.size(), x1.size());
  out()->add_block(odata, x0, x3, x2, x1);
}

void Task611::Task_local::compute() {
  const Index x0 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x1 = b(3);
  // tensor label: I739
  std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x0);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x0)]);
  sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x3.size(), x0.size());
  // tensor label (calculated on-the-fly): Gamma262
  // associated with merged
  std::unique_ptr<double[]> fdata = in(1)->get_block(x2, x1);
  if (x0 == x3) {
    std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x2, x1)]);
    std::fill_n(o1data.get(), out(1)->get_size(x2, x1), 0.0);
    for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
      for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          o1data[ix2+x2.size()*(ix1)] += 
            2.0 * fdata[ix2+x2.size()*(ix1)] * i0data_sorted[ix3+x0.size()*(ix3)];
        }
      }
    }
    out(1)->add_block(o1data, x2, x1);
  }
  // rdm0 merged ci derivative case
  if (x2 == x3 && x0 == x1) {
    std::unique_ptr<double[]> o0data(new double[out(0)->get_size()]);
    std::fill_n(o0data.get(), out(0)->get_size(), 0.0);
    for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
      for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
        o0data[0] += 
          2.0 * fdata[ix3+x2.size()*(ix1)] * i0data_sorted[ix1+x0.size()*(ix3)];
      }
    }
    out(0)->add_block(o0data);
  }
  if (x0 == x1) {
    std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x2, x3)]);
    std::fill_n(o1data.get(), out(1)->get_size(x2, x3), 0.0);
    for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
      for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
        for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
          o1data[ix2+x2.size()*(ix3)] += 
            -1.0 * fdata[ix2+x2.size()*(ix1)] * i0data_sorted[ix1+x0.size()*(ix3)];
        }
      }
    }
    out(1)->add_block(o1data, x2, x3);
  }
  if (x2 == x3) {
    std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x0, x1)]);
    std::fill_n(o1data.get(), out(1)->get_size(x0, x1), 0.0);
    for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          o1data[ix0+x0.size()*(ix1)] += 
            -1.0 * fdata[ix3+x2.size()*(ix1)] * i0data_sorted[ix0+x0.size()*(ix3)];
        }
      }
    }
    out(1)->add_block(o1data, x0, x1);
  }
  {
    std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x0, x3, x2, x1)]);
    std::fill_n(o2data.get(), out(2)->get_size(x0, x3, x2, x1), 0.0);
    for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
      for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
            o2data[ix0+x0.size()*(ix3+x3.size()*(ix2+x2.size()*(ix1)))] += 
              -1.0 * fdata[ix2+x2.size()*(ix1)] * i0data_sorted[ix0+x0.size()*(ix3)];
          }
        }
      }
    }
    out(2)->add_block(o2data, x0, x3, x2, x1);
  }
}

void Task612::Task_local::compute() {
  const Index x3 = b(0);
  const Index x0 = b(1);
  // tensor label: I739
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, x0)]);
  std::fill_n(odata.get(), out()->get_size(x3, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x0), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I740
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x3);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x3)]);
        sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x3.size());
        dgemm_("T", "N", x0.size(), x3.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), x3.size());
  out()->add_block(odata, x3, x0);
}

void Task613::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x3 = b(3);
  // tensor label: I740
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x3)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x3), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c1, x3);
    sort_indices<0,1,2,3,1,1,-2,1>(i0data, odata, c3.size(), a2.size(), c1.size(), x3.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x3);
    sort_indices<2,1,0,3,1,1,4,1>(i1data, odata, c1.size(), a2.size(), c3.size(), x3.size());
  }
  out()->add_block(odata, c3, a2, c1, x3);
}

void Task614::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1)]);
  sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size());
  // tensor label (calculated on-the-fly): Gamma264
  {
    // rdm0 non-merged ci derivative case
    if (x0 == x1) {
      std::unique_ptr<double[]> o0data(new double[out(0)->get_size()]);
      std::fill_n(o0data.get(), out(0)->get_size(), 0.0);
      for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
        o0data[0] +=
          2.0 * i0data_sorted[ix1+x0.size()*(ix1)];
      }
      out(0)->add_block(o0data);
    }
  }
  {
    std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x0, x1)]);
    std::fill_n(o1data.get(), out(1)->get_size(x0, x1), 0.0);
    sort_indices<0,1,1,1,-1,1>(i0data_sorted, o1data, x0.size(), x1.size());
    out(1)->add_block(o1data, x0, x1);
  }
}

void Task615::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c4 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c3 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c4, a2, c3, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c4, a2, c3, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c4.size(), a2.size(), c3.size(), x1.size());
        // tensor label: I746
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, a2, c4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, a2, c4)]);
        sort_indices<3,2,1,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), a2.size(), c4.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*a2.size()*c4.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c4.size(), i1data_sorted, c3.size()*a2.size()*c4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task616::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index c4 = b(3);
  // tensor label: I746
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, a2, c4)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, a2, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, a2, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, a2, c4), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, c4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, c4)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), c4.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<0,1,2,3,0,1,-4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", c4.size(), x0.size()*c3.size()*a2.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, c4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, c4.size(), a2.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, a2, c4);
}

void Task617::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c4 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c4, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a2, c4, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), a2.size(), c4.size(), x1.size());
        // tensor label: I750
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, a2, c4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, a2, c4)]);
        sort_indices<1,2,3,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), a2.size(), c4.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*a2.size()*c4.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c4.size(), i1data_sorted, c3.size()*a2.size()*c4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task618::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index c4 = b(3);
  // tensor label: I750
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, a2, c4)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, a2, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, a2, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, a2, c4), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, c4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, c4)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), c4.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<0,1,2,3,0,1,2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", c4.size(), x0.size()*c3.size()*a2.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, c4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, c4.size(), a2.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, a2, c4);
}

void Task619::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c4 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c4, a2, c1, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c4, a2, c1, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c4.size(), a2.size(), c1.size(), x1.size());
        // tensor label: I754
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a2, c1, c4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a2, c1, c4)]);
        sort_indices<3,1,2,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), a2.size(), c1.size(), c4.size());
        dgemm_("T", "N", x1.size(), x0.size(), a2.size()*c1.size()*c4.size(),
               1.0, i0data_sorted, a2.size()*c1.size()*c4.size(), i1data_sorted, a2.size()*c1.size()*c4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task620::Task_local::compute() {
  const Index x0 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index c4 = b(3);
  // tensor label: I754
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a2, c1, c4)]);
  std::fill_n(odata.get(), out()->get_size(x0, a2, c1, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a2, c1, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a2, c1, c4), 0.0);
  for (auto& c3 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, c4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, c4)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), c4.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<2,0,1,3,0,1,2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", c4.size(), x0.size()*a2.size()*c1.size(), c3.size(),
           1.0, i0data_sorted, c3.size(), i1data_sorted, c3.size(),
           1.0, odata_sorted, c4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c1.size(), a2.size(), x0.size());
  out()->add_block(odata, x0, a2, c1, c4);
}

void Task621::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a4 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a4, c1, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, a4, c1, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c3.size(), a4.size(), c1.size(), x1.size());
        // tensor label: I758
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, c1, a4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, c1, a4)]);
        sort_indices<1,3,2,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), c1.size(), a4.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*c1.size()*a4.size(),
               1.0, i0data_sorted, c3.size()*c1.size()*a4.size(), i1data_sorted, c3.size()*c1.size()*a4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task622::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index c1 = b(2);
  const Index a4 = b(3);
  // tensor label: I758
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, c1, a4)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, c1, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, c1, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, c1, a4), 0.0);
  for (auto& a2 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a4, a2)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, a4.size(), a2.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<1,0,2,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", a4.size(), x0.size()*c3.size()*c1.size(), a2.size(),
           1.0, i0data_sorted, a2.size(), i1data_sorted, a2.size(),
           1.0, odata_sorted, a4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, a4.size(), c1.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, c1, a4);
}

void Task623::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c4 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c4, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c4, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c4.size(), x1.size());
        // tensor label: I762
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a2, c1, c4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a2, c1, c4)]);
        sort_indices<2,1,3,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), a2.size(), c1.size(), c4.size());
        dgemm_("T", "N", x1.size(), x0.size(), a2.size()*c1.size()*c4.size(),
               1.0, i0data_sorted, a2.size()*c1.size()*c4.size(), i1data_sorted, a2.size()*c1.size()*c4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task624::Task_local::compute() {
  const Index x0 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index c4 = b(3);
  // tensor label: I762
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, a2, c1, c4)]);
  std::fill_n(odata.get(), out()->get_size(x0, a2, c1, c4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, a2, c1, c4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, a2, c1, c4), 0.0);
  for (auto& c3 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, c4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, c4)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), c4.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<2,0,1,3,0,1,-4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", c4.size(), x0.size()*a2.size()*c1.size(), c3.size(),
           1.0, i0data_sorted, c3.size(), i1data_sorted, c3.size(),
           1.0, odata_sorted, c4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, c4.size(), c1.size(), a2.size(), x0.size());
  out()->add_block(odata, x0, a2, c1, c4);
}

void Task625::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& a4 : *range_[2]) {
      for (auto& c3 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a4, c3, x1);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a4, c3, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a4.size(), c3.size(), x1.size());
        // tensor label: I766
        std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, c1, a4);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, c1, a4)]);
        sort_indices<2,3,1,0,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), c1.size(), a4.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*c1.size()*a4.size(),
               1.0, i0data_sorted, c3.size()*c1.size()*a4.size(), i1data_sorted, c3.size()*c1.size()*a4.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task626::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index c1 = b(2);
  const Index a4 = b(3);
  // tensor label: I766
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, c1, a4)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, c1, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, c1, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, c1, a4), 0.0);
  for (auto& a2 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a4, a2)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, a4.size(), a2.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<1,0,2,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", a4.size(), x0.size()*c3.size()*c1.size(), a2.size(),
           1.0, i0data_sorted, a2.size(), i1data_sorted, a2.size(),
           1.0, odata_sorted, a4.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, a4.size(), c1.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, c1, a4);
}

void Task627::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& a4 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(a4, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(a4, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, a4.size(), x1.size());
    // tensor label: I786
    std::unique_ptr<double[]> i1data = in(1)->get_block(a4, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a4, x0)]);
    sort_indices<0,1,0,1,1,1>(i1data, i1data_sorted, a4.size(), x0.size());
    dgemm_("T", "N", x1.size(), x0.size(), a4.size(),
           1.0, i0data_sorted, a4.size(), i1data_sorted, a4.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task628::Task_local::compute() {
  const Index a4 = b(0);
  const Index x0 = b(1);
  // tensor label: I786
  std::unique_ptr<double[]> odata(new double[out()->get_size(a4, x0)]);
  std::fill_n(odata.get(), out()->get_size(a4, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a4, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a4, x0), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I787
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a4, c3, a2);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a4, c3, a2)]);
        sort_indices<2,3,0,1,0,1,1,1>(i1data, i1data_sorted, c1.size(), a4.size(), c3.size(), a2.size());
        dgemm_("T", "N", x0.size(), a4.size(), c1.size()*c3.size()*a2.size(),
               1.0, i0data_sorted, c1.size()*c3.size()*a2.size(), i1data_sorted, c1.size()*c3.size()*a2.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x0.size(), a4.size());
  out()->add_block(odata, a4, x0);
}

void Task629::Task_local::compute() {
  const Index c1 = b(0);
  const Index a4 = b(1);
  const Index c3 = b(2);
  const Index a2 = b(3);
  // tensor label: I787
  std::unique_ptr<double[]> odata(new double[out()->get_size(c1, a4, c3, a2)]);
  std::fill_n(odata.get(), out()->get_size(c1, a4, c3, a2), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a4, c3, a2);
    sort_indices<0,1,2,3,1,1,-4,1>(i0data, odata, c1.size(), a4.size(), c3.size(), a2.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, a4);
    sort_indices<0,3,2,1,1,1,8,1>(i1data, odata, c1.size(), a2.size(), c3.size(), a4.size());
  }
  out()->add_block(odata, c1, a4, c3, a2);
}

void Task630::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& a2 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a2);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a2)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x0.size(), a2.size());
    // tensor label: I929
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a2)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, x1.size(), a2.size());
    dgemm_("T", "N", x0.size(), x1.size(), a2.size(),
           1.0, i0data_sorted, a2.size(), i1data_sorted, a2.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size());
  out()->add_block(odata, x0, x1);
}

void Task631::Task_local::compute() {
  const Index x1 = b(0);
  const Index a2 = b(1);
  // tensor label: I929
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a2)]);
  std::fill_n(odata.get(), out()->get_size(x1, a2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, a2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, a2), 0.0);
  for (auto& a4 : *range_[2]) {
    for (auto& c3 : *range_[0]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, a4);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, a4)]);
        sort_indices<3,2,0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), a4.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a4, c3, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a4, c3, x1)]);
        sort_indices<1,2,0,3,0,1,-4,1>(i1data, i1data_sorted, c1.size(), a4.size(), c3.size(), x1.size());
        dgemm_("T", "N", a2.size(), x1.size(), c1.size()*a4.size()*c3.size(),
               1.0, i0data_sorted, c1.size()*a4.size()*c3.size(), i1data_sorted, c1.size()*a4.size()*c3.size(),
               1.0, odata_sorted, a2.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a2.size(), x1.size());
  out()->add_block(odata, x1, a2);
}

void Task632::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& a4 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a4);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a4)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x0.size(), a4.size());
    // tensor label: I933
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, a4);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, a4)]);
    sort_indices<1,0,0,1,1,1>(i1data, i1data_sorted, x1.size(), a4.size());
    dgemm_("T", "N", x0.size(), x1.size(), a4.size(),
           1.0, i0data_sorted, a4.size(), i1data_sorted, a4.size(),
           1.0, odata_sorted, x0.size());
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size());
  out()->add_block(odata, x0, x1);
}

void Task633::Task_local::compute() {
  const Index x1 = b(0);
  const Index a4 = b(1);
  // tensor label: I933
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, a4)]);
  std::fill_n(odata.get(), out()->get_size(x1, a4), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, a4)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, a4), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, a4);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, a4)]);
        sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), a4.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(0)->get_size(c1, a2, c3, x1)]);
        sort_indices<2,1,0,3,0,1,8,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x1.size());
        dgemm_("T", "N", a4.size(), x1.size(), c1.size()*a2.size()*c3.size(),
               1.0, i0data_sorted, c1.size()*a2.size()*c3.size(), i1data_sorted, c1.size()*a2.size()*c3.size(),
               1.0, odata_sorted, a4.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, a4.size(), x1.size());
  out()->add_block(odata, x1, a4);
}

void Task634::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& a2 : *range_[2]) {
      for (auto& c1 : *range_[0]) {
        // tensor label: t2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, a2, c3, x0)]);
        sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        // tensor label: I1070
        std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a2, c1, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a2, c1, x1)]);
        sort_indices<0,1,2,3,0,1,1,1>(i1data, i1data_sorted, c3.size(), a2.size(), c1.size(), x1.size());
        dgemm_("T", "N", x0.size(), x1.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size());
  out()->add_block(odata, x0, x1);
}

void Task635::Task_local::compute() {
  const Index c3 = b(0);
  const Index a2 = b(1);
  const Index c1 = b(2);
  const Index x1 = b(3);
  // tensor label: I1070
  std::unique_ptr<double[]> odata(new double[out()->get_size(c3, a2, c1, x1)]);
  std::fill_n(odata.get(), out()->get_size(c3, a2, c1, x1), 0.0);
  {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(c3, a2, c1, x1);
    dscal_(c3.size()*a2.size()*c1.size()*x1.size(), e0_, i0data.get(), 1);
    sort_indices<0,1,2,3,1,1,2,1>(i0data, odata, c3.size(), a2.size(), c1.size(), x1.size());
  }
  {
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(0)->get_block(c1, a2, c3, x1);
    dscal_(c1.size()*a2.size()*c3.size()*x1.size(), e0_, i1data.get(), 1);
    sort_indices<2,1,0,3,1,1,-4,1>(i1data, odata, c1.size(), a2.size(), c3.size(), x1.size());
  }
  out()->add_block(odata, c3, a2, c1, x1);
}

void Task636::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& c1 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, x1, c1, a2);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, x1, c1, a2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), x1.size(), c1.size(), a2.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
        sort_indices<2,0,1,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task637::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& c3 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x1, c3, a2);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x1, c3, a2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), x1.size(), c3.size(), a2.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
        sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
        dgemm_("T", "N", x1.size(), x0.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x1.size());
      }
    }
  }
  sort_indices<1,0,1,1,1,1>(odata_sorted, odata, x1.size(), x0.size());
  out()->add_block(odata, x0, x1);
}

void Task638::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c3 : *range_[0]) {
    for (auto& c1 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c3, x0, c1, a2);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c3, x0, c1, a2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c3.size(), x0.size(), c1.size(), a2.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x1)]);
        sort_indices<2,0,1,3,0,1,4,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x1.size());
        dgemm_("T", "N", x0.size(), x1.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size());
  out()->add_block(odata, x0, x1);
}

void Task639::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  // tensor label: I745
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    for (auto& c3 : *range_[0]) {
      for (auto& a2 : *range_[2]) {
        // tensor label: v2
        std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x0, c3, a2);
        std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x0, c3, a2)]);
        sort_indices<0,2,3,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), x0.size(), c3.size(), a2.size());
        // tensor label: t2
        std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x1);
        std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x1)]);
        sort_indices<0,2,1,3,0,1,-2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x1.size());
        dgemm_("T", "N", x0.size(), x1.size(), c3.size()*a2.size()*c1.size(),
               1.0, i0data_sorted, c3.size()*a2.size()*c1.size(), i1data_sorted, c3.size()*a2.size()*c1.size(),
               1.0, odata_sorted, x0.size());
      }
    }
  }
  sort_indices<0,1,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size());
  out()->add_block(odata, x0, x1);
}

void Task640::Task_local::compute() {
  const Index x3 = b(0);
  const Index x1 = b(1);
  const Index x0 = b(2);
  const Index x2 = b(3);
  // tensor label: I769
  std::unique_ptr<double[]> i0data = in(0)->get_block(x0, x1, x3, x2);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, x1, x3, x2)]);
  sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), x1.size(), x3.size(), x2.size());
  // tensor label (calculated on-the-fly): Gamma270
  {
    if (x0 == x1) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x3, x2)]);
      std::fill_n(o1data.get(), out(1)->get_size(x3, x2), 0.0);
      for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
        for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
          for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
            o1data[ix3+x3.size()*(ix2)] +=
              1.0 * i0data_sorted[ix3+x3.size()*(ix1+x1.size()*(ix1+x0.size()*(ix2)))];
          }
        }
      }
      out(1)->add_block(o1data, x3, x2);
    }
  }
  {
    if (x0 == x2) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x3, x1)]);
      std::fill_n(o1data.get(), out(1)->get_size(x3, x1), 0.0);
      for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
        for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
          for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
            o1data[ix3+x3.size()*(ix1)] +=
              -2.0 * i0data_sorted[ix3+x3.size()*(ix1+x1.size()*(ix2+x0.size()*(ix2)))];
          }
        }
      }
      out(1)->add_block(o1data, x3, x1);
    }
  }
  {
    std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x3, x1, x0, x2)]);
    std::fill_n(o2data.get(), out(2)->get_size(x3, x1, x0, x2), 0.0);
    sort_indices<0,1,2,3,1,1,1,1>(i0data_sorted, o2data, x3.size(), x1.size(), x0.size(), x2.size());
    out(2)->add_block(o2data, x3, x1, x0, x2);
  }
}

void Task641::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I769
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1, x3, x2)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1, x3, x2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2), 0.0);
  for (auto& a2 : *range_[2]) {
    for (auto& c3 : *range_[0]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x3, a2, c3, x2);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, a2, c3, x2)]);
      sort_indices<1,2,0,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), a2.size(), c3.size(), x2.size());
      // tensor label: I770
      std::unique_ptr<double[]> i1data = in(1)->get_block(x0, c3, a2, x1);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, c3, a2, x1)]);
      sort_indices<2,1,0,3,0,1,1,1>(i1data, i1data_sorted, x0.size(), c3.size(), a2.size(), x1.size());
      dgemm_("T", "N", x3.size()*x2.size(), x0.size()*x1.size(), c3.size()*a2.size(),
             1.0, i0data_sorted, c3.size()*a2.size(), i1data_sorted, c3.size()*a2.size(),
             1.0, odata_sorted, x3.size()*x2.size());
    }
  }
  sort_indices<2,3,0,1,1,1,1,1>(odata_sorted, odata, x3.size(), x2.size(), x0.size(), x1.size());
  out()->add_block(odata, x0, x1, x3, x2);
}

void Task642::Task_local::compute() {
  const Index x0 = b(0);
  const Index c3 = b(1);
  const Index a2 = b(2);
  const Index x1 = b(3);
  // tensor label: I770
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, c3, a2, x1)]);
  std::fill_n(odata.get(), out()->get_size(x0, c3, a2, x1), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, c3, a2, x1)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, c3, a2, x1), 0.0);
  for (auto& c1 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(c1, x1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c1, x1)]);
    sort_indices<0,1,0,1,1,1>(i0data, i0data_sorted, c1.size(), x1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c1, a2, c3, x0);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c1, a2, c3, x0)]);
    sort_indices<0,1,2,3,0,1,2,1>(i1data, i1data_sorted, c1.size(), a2.size(), c3.size(), x0.size());
    dgemm_("T", "N", x1.size(), x0.size()*c3.size()*a2.size(), c1.size(),
           1.0, i0data_sorted, c1.size(), i1data_sorted, c1.size(),
           1.0, odata_sorted, x1.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x1.size(), a2.size(), c3.size(), x0.size());
  out()->add_block(odata, x0, c3, a2, x1);
}

void Task643::Task_local::compute() {
  const Index x0 = b(0);
  const Index x1 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I769
  std::unique_ptr<double[]> odata(new double[out()->get_size(x0, x1, x3, x2)]);
  std::fill_n(odata.get(), out()->get_size(x0, x1, x3, x2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x0, x1, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x0, x1, x3, x2), 0.0);
  for (auto& c2 : *range_[0]) {
    for (auto& a1 : *range_[2]) {
      // tensor label: v2
      std::unique_ptr<double[]> i0data = in(0)->get_block(c2, x0, x1, a1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(c2, x0, x1, a1)]);
      sort_indices<0,3,1,2,0,1,1,1>(i0data, i0data_sorted, c2.size(), x0.size(), x1.size(), a1.size());
      // tensor label: t2
      std::unique_ptr<double[]> i1data = in(1)->get_block(x3, a1, c2, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x3, a1, c2, x2)]);
      sort_indices<2,1,0,3,0,1,-1,1>(i1data, i1data_sorted, x3.size(), a1.size(), c2.size(), x2.size());
      dgemm_("T", "N", x0.size()*x1.size(), x2.size()*x3.size(), c2.size()*a1.size(),
             1.0, i0data_sorted, c2.size()*a1.size(), i1data_sorted, c2.size()*a1.size(),
             1.0, odata_sorted, x0.size()*x1.size());
    }
  }
  sort_indices<0,1,2,3,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), x3.size(), x2.size());
  out()->add_block(odata, x0, x1, x3, x2);
}

void Task644::Task_local::compute() {
  const Index x5 = b(0);
  const Index x4 = b(1);
  const Index x1 = b(2);
  const Index x3 = b(3);
  const Index x2 = b(4);
  const Index x0 = b(5);
  // tensor label: I793
  std::unique_ptr<double[]> i0data = in(0)->get_block(x1, x0, x2, x5, x4, x3);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x1, x0, x2, x5, x4, x3)]);
  sort_indices<3,4,0,5,2,1,0,1,1,1>(i0data, i0data_sorted, x1.size(), x0.size(), x2.size(), x5.size(), x4.size(), x3.size());
  // tensor label (calculated on-the-fly): Gamma276
  {
    if (x2 == x4 && x1 == x3) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x5, x0)]);
      std::fill_n(o1data.get(), out(1)->get_size(x5, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
            for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
              o1data[ix5+x5.size()*(ix0)] +=
                -2.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix3+x1.size()*(ix3+x3.size()*(ix4+x2.size()*(ix0)))))];
            }
          }
        }
      }
      out(1)->add_block(o1data, x5, x0);
    }
  }
  {
    if (x1 == x3) {
      std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x5, x4, x2, x0)]);
      std::fill_n(o2data.get(), out(2)->get_size(x5, x4, x2, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
          for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
            for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
              for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
                o2data[ix5+x5.size()*(ix4+x4.size()*(ix2+x2.size()*(ix0)))] +=
                  -2.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix3+x1.size()*(ix3+x3.size()*(ix2+x2.size()*(ix0)))))];
              }
            }
          }
        }
      }
      out(2)->add_block(o2data, x5, x4, x2, x0);
    }
  }
  {
    if (x2 == x3 && x1 == x4) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x5, x0)]);
      std::fill_n(o1data.get(), out(1)->get_size(x5, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
            for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
              o1data[ix5+x5.size()*(ix0)] +=
                1.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix4+x1.size()*(ix3+x3.size()*(ix3+x2.size()*(ix0)))))];
            }
          }
        }
      }
      out(1)->add_block(o1data, x5, x0);
    }
  }
  {
    if (x1 == x4) {
      std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x5, x3, x2, x0)]);
      std::fill_n(o2data.get(), out(2)->get_size(x5, x3, x2, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
          for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
            for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
              for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
                o2data[ix5+x5.size()*(ix3+x3.size()*(ix2+x2.size()*(ix0)))] +=
                  1.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix4+x1.size()*(ix3+x3.size()*(ix2+x2.size()*(ix0)))))];
              }
            }
          }
        }
      }
      out(2)->add_block(o2data, x5, x3, x2, x0);
    }
  }
  {
    if (x2 == x3) {
      std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x5, x4, x1, x0)]);
      std::fill_n(o2data.get(), out(2)->get_size(x5, x4, x1, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
            for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
              for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
                o2data[ix5+x5.size()*(ix4+x4.size()*(ix1+x1.size()*(ix0)))] +=
                  1.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix1+x1.size()*(ix3+x3.size()*(ix3+x2.size()*(ix0)))))];
              }
            }
          }
        }
      }
      out(2)->add_block(o2data, x5, x4, x1, x0);
    }
  }
  {
    if (x2 == x4) {
      std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x5, x0, x1, x3)]);
      std::fill_n(o2data.get(), out(2)->get_size(x5, x0, x1, x3), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
            for (int ix4 = 0; ix4 != x4.size(); ++ix4) {
              for (int ix5 = 0; ix5 != x5.size(); ++ix5) {
                o2data[ix5+x5.size()*(ix0+x0.size()*(ix1+x1.size()*(ix3)))] +=
                  1.0 * i0data_sorted[ix5+x5.size()*(ix4+x4.size()*(ix1+x1.size()*(ix3+x3.size()*(ix4+x2.size()*(ix0)))))];
              }
            }
          }
        }
      }
      out(2)->add_block(o2data, x5, x0, x1, x3);
    }
  }
  {
    std::unique_ptr<double[]> o3data(new double[out(3)->get_size(x5, x4, x1, x3, x2, x0)]);
    std::fill_n(o3data.get(), out(3)->get_size(x5, x4, x1, x3, x2, x0), 0.0);
    sort_indices<0,1,2,3,4,5,1,1,1,1>(i0data_sorted, o3data, x5.size(), x4.size(), x1.size(), x3.size(), x2.size(), x0.size());
    out(3)->add_block(o3data, x5, x4, x1, x3, x2, x0);
  }
}

void Task645::Task_local::compute() {
  const Index x1 = b(0);
  const Index x0 = b(1);
  const Index x2 = b(2);
  const Index x5 = b(3);
  const Index x4 = b(4);
  const Index x3 = b(5);
  // tensor label: I793
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, x0, x2, x5, x4, x3)]);
  std::fill_n(odata.get(), out()->get_size(x1, x0, x2, x5, x4, x3), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, x0, x2, x5, x4, x3)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, x0, x2, x5, x4, x3), 0.0);
  for (auto& c2 : *range_[0]) {
    // tensor label: t2
    std::unique_ptr<double[]> i0data = in(0)->get_block(x5, x4, c2, x3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x5, x4, c2, x3)]);
    sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, x5.size(), x4.size(), c2.size(), x3.size());
    // tensor label: I794
    std::unique_ptr<double[]> i1data = in(1)->get_block(x1, c2, x0, x2);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x1, c2, x0, x2)]);
    sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, x1.size(), c2.size(), x0.size(), x2.size());
    dgemm_("T", "N", x5.size()*x4.size()*x3.size(), x1.size()*x0.size()*x2.size(), c2.size(),
           1.0, i0data_sorted, c2.size(), i1data_sorted, c2.size(),
           1.0, odata_sorted, x5.size()*x4.size()*x3.size());
  }
  sort_indices<3,4,5,0,1,2,1,1,1,1>(odata_sorted, odata, x5.size(), x4.size(), x3.size(), x1.size(), x0.size(), x2.size());
  out()->add_block(odata, x1, x0, x2, x5, x4, x3);
}

void Task646::Task_local::compute() {
  const Index x1 = b(0);
  const Index c2 = b(1);
  const Index x0 = b(2);
  const Index x2 = b(3);
  // tensor label: I794
  std::unique_ptr<double[]> odata(new double[out()->get_size(x1, c2, x0, x2)]);
  std::fill_n(odata.get(), out()->get_size(x1, c2, x0, x2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x1, c2, x0, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x1, c2, x0, x2), 0.0);
  for (auto& a1 : *range_[2]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, a1);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x2, a1)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x2.size(), a1.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(x0, a1, c2, x1);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(x0, a1, c2, x1)]);
    sort_indices<1,0,2,3,0,1,-2,1>(i1data, i1data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
    dgemm_("T", "N", x2.size(), x1.size()*c2.size()*x0.size(), a1.size(),
           1.0, i0data_sorted, a1.size(), i1data_sorted, a1.size(),
           1.0, odata_sorted, x2.size());
  }
  sort_indices<3,2,1,0,1,1,1,1>(odata_sorted, odata, x2.size(), x0.size(), c2.size(), x1.size());
  out()->add_block(odata, x1, c2, x0, x2);
}

void Task647::Task_local::compute() {
  const Index x1 = b(0);
  const Index x3 = b(1);
  const Index x2 = b(2);
  const Index x0 = b(3);
  // tensor label: I797
  std::unique_ptr<double[]> i0data = in(0)->get_block(x3, x2, x1, x0);
  std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x3, x2, x1, x0)]);
  sort_indices<2,0,1,3,0,1,1,1>(i0data, i0data_sorted, x3.size(), x2.size(), x1.size(), x0.size());
  // tensor label (calculated on-the-fly): Gamma277
  {
    if (x1 == x3) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x2, x0)]);
      std::fill_n(o1data.get(), out(1)->get_size(x2, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix2 = 0; ix2 != x2.size(); ++ix2) {
          for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
            o1data[ix2+x2.size()*(ix0)] +=
              -2.0 * i0data_sorted[ix3+x1.size()*(ix3+x3.size()*(ix2+x2.size()*(ix0)))];
          }
        }
      }
      out(1)->add_block(o1data, x2, x0);
    }
  }
  {
    if (x2 == x3) {
      std::unique_ptr<double[]> o1data(new double[out(1)->get_size(x1, x0)]);
      std::fill_n(o1data.get(), out(1)->get_size(x1, x0), 0.0);
      for (int ix0 = 0; ix0 != x0.size(); ++ix0) {
        for (int ix3 = 0; ix3 != x3.size(); ++ix3) {
          for (int ix1 = 0; ix1 != x1.size(); ++ix1) {
            o1data[ix1+x1.size()*(ix0)] +=
              1.0 * i0data_sorted[ix1+x1.size()*(ix3+x3.size()*(ix3+x2.size()*(ix0)))];
          }
        }
      }
      out(1)->add_block(o1data, x1, x0);
    }
  }
  {
    std::unique_ptr<double[]> o2data(new double[out(2)->get_size(x1, x3, x2, x0)]);
    std::fill_n(o2data.get(), out(2)->get_size(x1, x3, x2, x0), 0.0);
    sort_indices<0,1,2,3,1,1,1,1>(i0data_sorted, o2data, x1.size(), x3.size(), x2.size(), x0.size());
    out(2)->add_block(o2data, x1, x3, x2, x0);
  }
}

void Task648::Task_local::compute() {
  const Index x3 = b(0);
  const Index x2 = b(1);
  const Index x1 = b(2);
  const Index x0 = b(3);
  // tensor label: I797
  std::unique_ptr<double[]> odata(new double[out()->get_size(x3, x2, x1, x0)]);
  std::fill_n(odata.get(), out()->get_size(x3, x2, x1, x0), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(x3, x2, x1, x0)]);
  std::fill_n(odata_sorted.get(), out()->get_size(x3, x2, x1, x0), 0.0);
  for (auto& c2 : *range_[0]) {
    for (auto& a1 : *range_[2]) {
      // tensor label: t2
      std::unique_ptr<double[]> i0data = in(0)->get_block(x0, a1, c2, x1);
      std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x0, a1, c2, x1)]);
      sort_indices<2,1,0,3,0,1,1,1>(i0data, i0data_sorted, x0.size(), a1.size(), c2.size(), x1.size());
      // tensor label: I798
      std::unique_ptr<double[]> i1data = in(1)->get_block(a1, c2, x3, x2);
      std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(a1, c2, x3, x2)]);
      sort_indices<1,0,2,3,0,1,1,1>(i1data, i1data_sorted, a1.size(), c2.size(), x3.size(), x2.size());
      dgemm_("T", "N", x1.size()*x0.size(), x3.size()*x2.size(), a1.size()*c2.size(),
             1.0, i0data_sorted, a1.size()*c2.size(), i1data_sorted, a1.size()*c2.size(),
             1.0, odata_sorted, x1.size()*x0.size());
    }
  }
  sort_indices<2,3,1,0,1,1,1,1>(odata_sorted, odata, x0.size(), x1.size(), x3.size(), x2.size());
  out()->add_block(odata, x3, x2, x1, x0);
}

void Task649::Task_local::compute() {
  const Index a1 = b(0);
  const Index c2 = b(1);
  const Index x3 = b(2);
  const Index x2 = b(3);
  // tensor label: I798
  std::unique_ptr<double[]> odata(new double[out()->get_size(a1, c2, x3, x2)]);
  std::fill_n(odata.get(), out()->get_size(a1, c2, x3, x2), 0.0);
  std::unique_ptr<double[]> odata_sorted(new double[out()->get_size(a1, c2, x3, x2)]);
  std::fill_n(odata_sorted.get(), out()->get_size(a1, c2, x3, x2), 0.0);
  for (auto& c3 : *range_[0]) {
    // tensor label: f1
    std::unique_ptr<double[]> i0data = in(0)->get_block(x2, c3);
    std::unique_ptr<double[]> i0data_sorted(new double[in(0)->get_size(x2, c3)]);
    sort_indices<1,0,0,1,1,1>(i0data, i0data_sorted, x2.size(), c3.size());
    // tensor label: t2
    std::unique_ptr<double[]> i1data = in(1)->get_block(c3, a1, c2, x3);
    std::unique_ptr<double[]> i1data_sorted(new double[in(1)->get_size(c3, a1, c2, x3)]);
    sort_indices<0,1,2,3,0,1,2,1>(i1data, i1data_sorted, c3.size(), a1.size(), c2.size(), x3.size());
    dgemm_("T", "N", x2.size(), a1.size()*c2.size()*x3.size(), c3.size(),
           1.0, i0data_sorted, c3.size(), i1data_sorted, c3.size(),
           1.0, odata_sorted, x2.size());
  }
  sort_indices<1,2,3,0,1,1,1,1>(odata_sorted, odata, x2.size(), a1.size(), c2.size(), x3.size());
  out()->add_block(odata, a1, c2, x3, x2);
}

#endif
