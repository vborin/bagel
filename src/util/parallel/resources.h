//
// BAGEL - Brilliantly Advanced General Electronic Structure Library
// Filename: resources.h
// Copyright (C) 2011 Toru Shiozaki
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

#ifndef __SRC_PARALLEL_RESOURCES_H
#define __SRC_PARALLEL_RESOURCES_H

// CAUTION last-in-first-out stack to avoid the overhead of new'ing every time

#include <stddef.h>
#include <memory>
#include <atomic>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <complex>
#include <map>
#ifdef LIBINT_INTERFACE
  #include <libint2.h>
#endif
#include <src/util/parallel/process.h>
#include <src/util/constants.h>

namespace bagel {

 class StackMem {
  protected:
    std::unique_ptr<double[]> stack_area_;
    size_t pointer_;
    const size_t total_;

#ifdef LIBINT_INTERFACE
    std::unique_ptr<Libint_t[]> libint_t_;
#endif

  public:
    StackMem() : pointer_(0LU), total_(20000000LU) { // TODO 80MByte
      stack_area_ = std::unique_ptr<double[]>(new double[total_]);

      // in case we use Libint for ERI
    #ifdef LIBINT_INTERFACE
      // TODO 20LU should not be hardwired
      libint_t_ = std::unique_ptr<Libint_t[]>(new Libint_t[20LU*20LU*20LU*20LU]);
      if (libint2_need_memory_3eri1(LIBINT2_MAX_AM_3eri1) < libint2_need_memory_eri(LIBINT2_MAX_AM_eri)) {
        LIBINT2_PREFIXED_NAME(libint2_init_eri)(&libint_t_[0], LIBINT2_MAX_AM_eri, 0);
      } else {
        LIBINT2_PREFIXED_NAME(libint2_init_3eri1)(&libint_t_[0], LIBINT2_MAX_AM_3eri1, 0);
      }
    #endif
    }

    template <typename DataType = double>
    DataType* get(const size_t size) {
      assert(pointer_ + size < total_);
      assert(size * sizeof(DataType) % sizeof(double) == 0);
      DataType* out = reinterpret_cast<DataType*> (stack_area_.get() + pointer_);
      pointer_ += (size * sizeof(DataType) / sizeof(double));
      return out;
    }

    template <typename DataType = double>
    void release(const size_t size, DataType* p) {
      assert(size * sizeof(DataType) % sizeof(double) == 0);
      pointer_ -= (size * sizeof(DataType) / sizeof(double));
      assert(p == reinterpret_cast<DataType*> (stack_area_.get()+pointer_) || size == 0);
    }

    void clear() { pointer_ = 0LU; }
    size_t pointer() const { return pointer_; }

#ifdef LIBINT_INTERFACE
    Libint_t* libint_t_ptr(const int i) { return &libint_t_[i]; }
#endif

};


 class Resources {
  private:
    std::shared_ptr<Process> proc_;
    std::map<std::shared_ptr<StackMem>, std::atomic_flag> stackmem_;
    size_t max_num_threads_;

  public:
    Resources(const int max) : proc_(std::make_shared<Process>()), max_num_threads_(max) {
#ifdef LIBINT_INTERFACE
      LIBINT2_PREFIXED_NAME(libint2_static_init)();
#endif
      for (int i = 0; i != max; ++i)
        stackmem_[std::make_shared<StackMem>()].clear();
    }

    std::shared_ptr<StackMem> get() {
      for (auto& i : stackmem_) {
        if (!i.second.test_and_set())
          return i.first;
      }
      // This error most often occurs if we forget to destruct one integral object before constructing another
      throw std::runtime_error("Stack Memory exhausted");
      return nullptr;
    }

    void release(std::shared_ptr<StackMem> o) {
      o->clear();
      auto iter = stackmem_.find(o);
      assert(iter != stackmem_.end());
      iter->second.clear();
    }

    size_t max_num_threads() const { return max_num_threads_; }
    std::shared_ptr<Process> proc() { return proc_; }
};

extern Resources* resources__;

}

#endif
