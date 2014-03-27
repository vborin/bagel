//
// BAGEL - Parallel electron correlation program.
// Filename: CAS_test.h
// Copyright (C) 2012 Shiozaki group
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


#ifndef __SRC_SMITH_CAS_test_H
#define __SRC_SMITH_CAS_test_H

#include <src/smith/spinfreebase.h>
#include <src/scf/fock.h>
#include <src/util/f77.h>
#include <iostream>
#include <tuple>
#include <iomanip>
#include <src/smith/queue.h>
#include <src/smith/CAS_test_tasks.h>
#include <src/smith/smith_info.h>

namespace bagel {
namespace SMITH {
namespace CAS_test{

template <typename T>
class CAS_test : public SpinFreeMethod<T> {
  protected:
    using SpinFreeMethod<T>::ref_;

    std::shared_ptr<Tensor<T>> t2;
    std::shared_ptr<Tensor<T>> r;
    double e0_;
    std::shared_ptr<Tensor<T>> den1;
    std::shared_ptr<Tensor<T>> den2;
    double correct_den1;
    std::shared_ptr<Tensor<T>> deci;

    std::tuple<std::shared_ptr<Queue<T>>, std::shared_ptr<Queue<T>>, std::shared_ptr<Queue<T>>, std::shared_ptr<Queue<T>>, std::shared_ptr<Queue<T>>, std::shared_ptr<Queue<T>>> make_queue_() {
      std::shared_ptr<Queue<T>> queue_(new Queue<T>());
      std::array<std::shared_ptr<const IndexRange>,3> pindex = {{this->rclosed_, this->ractive_, this->rvirt_}};
      std::array<std::shared_ptr<const IndexRange>,4> cindex = {{this->rclosed_, this->ractive_, this->rvirt_, this->rci_}};

      std::vector<std::shared_ptr<Tensor<T>>> tensor0 = {r};
      std::shared_ptr<Task0<T>> task0(new Task0<T>(tensor0));
      queue_->add_task(task0);

      std::vector<IndexRange> Gamma0_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> Gamma0(new Tensor<T>(Gamma0_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor1 = {Gamma0, this->rdm3_, this->f1_};
      std::shared_ptr<Task1<T>> task1(new Task1<T>(tensor1, pindex));
      task1->add_dep(task0);
      queue_->add_task(task1);

      std::vector<IndexRange> Gamma2_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> Gamma2(new Tensor<T>(Gamma2_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor2 = {Gamma2, this->rdm2_};
      std::shared_ptr<Task2<T>> task2(new Task2<T>(tensor2, pindex));
      task2->add_dep(task0);
      queue_->add_task(task2);

      std::vector<IndexRange> Gamma8_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> Gamma8(new Tensor<T>(Gamma8_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor3 = {Gamma8, this->rdm3deriv_, this->f1_};
      std::shared_ptr<Task3<T>> task3(new Task3<T>(tensor3, cindex));
      task3->add_dep(task0);
      queue_->add_task(task3);

      std::vector<IndexRange> Gamma9_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> Gamma9(new Tensor<T>(Gamma9_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor4 = {Gamma9, this->rdm2deriv_};
      std::shared_ptr<Task4<T>> task4(new Task4<T>(tensor4, cindex));
      task4->add_dep(task0);
      queue_->add_task(task4);

      std::vector<IndexRange> Gamma17_index = {this->active_, this->active_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> Gamma17(new Tensor<T>(Gamma17_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor5 = {Gamma17, this->rdm3_};
      std::shared_ptr<Task5<T>> task5(new Task5<T>(tensor5, pindex));
      task5->add_dep(task0);
      queue_->add_task(task5);

      std::vector<IndexRange> I0_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I0(new Tensor<T>(I0_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor6 = {r, I0};
      std::shared_ptr<Task6<T>> task6(new Task6<T>(tensor6, pindex));
      task6->add_dep(task0);
      queue_->add_task(task6);


      std::vector<IndexRange> I1_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I1(new Tensor<T>(I1_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor7 = {I0, t2, I1};
      std::shared_ptr<Task7<T>> task7(new Task7<T>(tensor7, pindex));
      task6->add_dep(task7);
      task7->add_dep(task0);
      queue_->add_task(task7);


      std::vector<std::shared_ptr<Tensor<T>>> tensor8 = {I1, Gamma0};
      std::shared_ptr<Task8<T>> task8(new Task8<T>(tensor8, pindex));
      task7->add_dep(task8);
      task8->add_dep(task0);
      queue_->add_task(task8);

      task8->add_dep(task1);

      std::vector<IndexRange> I6_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I6(new Tensor<T>(I6_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor9 = {I0, t2, I6};
      std::shared_ptr<Task9<T>> task9(new Task9<T>(tensor9, pindex));
      task6->add_dep(task9);
      task9->add_dep(task0);
      queue_->add_task(task9);


      std::vector<std::shared_ptr<Tensor<T>>> tensor10 = {I6, Gamma2};
      std::shared_ptr<Task10<T>> task10(new Task10<T>(tensor10, pindex, this->e0_));
      task9->add_dep(task10);
      task10->add_dep(task0);
      queue_->add_task(task10);

      task10->add_dep(task2);

      std::vector<IndexRange> I8_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I8(new Tensor<T>(I8_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor11 = {I0, this->v2_, I8};
      std::shared_ptr<Task11<T>> task11(new Task11<T>(tensor11, pindex));
      task6->add_dep(task11);
      task11->add_dep(task0);
      queue_->add_task(task11);


      std::vector<std::shared_ptr<Tensor<T>>> tensor12 = {I8, Gamma2};
      std::shared_ptr<Task12<T>> task12(new Task12<T>(tensor12, pindex));
      task11->add_dep(task12);
      task12->add_dep(task0);
      queue_->add_task(task12);

      task12->add_dep(task2);

      std::vector<IndexRange> I2_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I2(new Tensor<T>(I2_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor13 = {r, I2};
      std::shared_ptr<Task13<T>> task13(new Task13<T>(tensor13, pindex));
      task13->add_dep(task0);
      queue_->add_task(task13);


      std::vector<IndexRange> I3_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I3(new Tensor<T>(I3_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor14 = {I2, this->f1_, I3};
      std::shared_ptr<Task14<T>> task14(new Task14<T>(tensor14, pindex));
      task13->add_dep(task14);
      task14->add_dep(task0);
      queue_->add_task(task14);


      std::vector<IndexRange> I4_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I4(new Tensor<T>(I4_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor15 = {I3, t2, I4};
      std::shared_ptr<Task15<T>> task15(new Task15<T>(tensor15, pindex));
      task14->add_dep(task15);
      task15->add_dep(task0);
      queue_->add_task(task15);


      std::vector<std::shared_ptr<Tensor<T>>> tensor16 = {I4, Gamma2};
      std::shared_ptr<Task16<T>> task16(new Task16<T>(tensor16, pindex));
      task15->add_dep(task16);
      task16->add_dep(task0);
      queue_->add_task(task16);

      task16->add_dep(task2);

      std::shared_ptr<Queue<T>> energy_(new Queue<T>());
      std::vector<IndexRange> I9_index;
      std::shared_ptr<Tensor<T>> I9(new Tensor<T>(I9_index, false));
      std::vector<IndexRange> I10_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I10(new Tensor<T>(I10_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor17 = {I9, t2, I10};
      std::shared_ptr<Task17<T>> task17(new Task17<T>(tensor17, pindex));
      energy_->add_task(task17);


      std::vector<IndexRange> I11_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I11(new Tensor<T>(I11_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor18 = {I10, t2, I11};
      std::shared_ptr<Task18<T>> task18(new Task18<T>(tensor18, pindex));
      task17->add_dep(task18);
      energy_->add_task(task18);


      std::vector<std::shared_ptr<Tensor<T>>> tensor19 = {I11, Gamma0};
      std::shared_ptr<Task19<T>> task19(new Task19<T>(tensor19, pindex));
      task18->add_dep(task19);
      energy_->add_task(task19);

      task19->add_dep(task1);

      std::vector<IndexRange> I14_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I14(new Tensor<T>(I14_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor20 = {I10, this->f1_, I14};
      std::shared_ptr<Task20<T>> task20(new Task20<T>(tensor20, pindex));
      task17->add_dep(task20);
      energy_->add_task(task20);


      std::vector<IndexRange> I15_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I15(new Tensor<T>(I15_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor21 = {I14, t2, I15};
      std::shared_ptr<Task21<T>> task21(new Task21<T>(tensor21, pindex));
      task20->add_dep(task21);
      energy_->add_task(task21);


      std::vector<std::shared_ptr<Tensor<T>>> tensor22 = {I15, Gamma2};
      std::shared_ptr<Task22<T>> task22(new Task22<T>(tensor22, pindex));
      task21->add_dep(task22);
      energy_->add_task(task22);

      task22->add_dep(task2);

      std::vector<IndexRange> I18_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I18(new Tensor<T>(I18_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor23 = {I10, t2, I18};
      std::shared_ptr<Task23<T>> task23(new Task23<T>(tensor23, pindex));
      task17->add_dep(task23);
      energy_->add_task(task23);


      std::vector<std::shared_ptr<Tensor<T>>> tensor24 = {I18, Gamma2};
      std::shared_ptr<Task24<T>> task24(new Task24<T>(tensor24, pindex, this->e0_));
      task23->add_dep(task24);
      energy_->add_task(task24);

      task24->add_dep(task2);

      std::vector<IndexRange> I21_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I21(new Tensor<T>(I21_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor25 = {I10, this->v2_, I21};
      std::shared_ptr<Task25<T>> task25(new Task25<T>(tensor25, pindex));
      task17->add_dep(task25);
      energy_->add_task(task25);


      std::vector<std::shared_ptr<Tensor<T>>> tensor26 = {I21, Gamma2};
      std::shared_ptr<Task26<T>> task26(new Task26<T>(tensor26, pindex));
      task25->add_dep(task26);
      energy_->add_task(task26);

      task26->add_dep(task2);

      std::shared_ptr<Queue<T>> dedci_(new Queue<T>());
      std::vector<std::shared_ptr<Tensor<T>>> tensor27 = {deci};
      std::shared_ptr<Task27<T>> task27(new Task27<T>(tensor27));
      dedci_->add_task(task27);

      std::vector<IndexRange> I22_index = {this->ci_};
      std::shared_ptr<Tensor<T>> I22(new Tensor<T>(I22_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor28 = {deci, I22};
      std::shared_ptr<Task28<T>> task28(new Task28<T>(tensor28, cindex));
      task28->add_dep(task27);
      dedci_->add_task(task28);


      std::vector<IndexRange> I23_index = {this->ci_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I23(new Tensor<T>(I23_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor29 = {I22, t2, I23};
      std::shared_ptr<Task29<T>> task29(new Task29<T>(tensor29, cindex));
      task28->add_dep(task29);
      task29->add_dep(task27);
      dedci_->add_task(task29);


      std::vector<IndexRange> I24_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I24(new Tensor<T>(I24_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor30 = {I23, t2, I24};
      std::shared_ptr<Task30<T>> task30(new Task30<T>(tensor30, cindex));
      task29->add_dep(task30);
      task30->add_dep(task27);
      dedci_->add_task(task30);


      std::vector<std::shared_ptr<Tensor<T>>> tensor31 = {I24, Gamma8};
      std::shared_ptr<Task31<T>> task31(new Task31<T>(tensor31, cindex));
      task30->add_dep(task31);
      task31->add_dep(task27);
      dedci_->add_task(task31);

      task31->add_dep(task3);

      std::vector<IndexRange> I27_index = {this->ci_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I27(new Tensor<T>(I27_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor32 = {I23, this->f1_, I27};
      std::shared_ptr<Task32<T>> task32(new Task32<T>(tensor32, cindex));
      task29->add_dep(task32);
      task32->add_dep(task27);
      dedci_->add_task(task32);


      std::vector<IndexRange> I28_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I28(new Tensor<T>(I28_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor33 = {I27, t2, I28};
      std::shared_ptr<Task33<T>> task33(new Task33<T>(tensor33, cindex));
      task32->add_dep(task33);
      task33->add_dep(task27);
      dedci_->add_task(task33);


      std::vector<std::shared_ptr<Tensor<T>>> tensor34 = {I28, Gamma9};
      std::shared_ptr<Task34<T>> task34(new Task34<T>(tensor34, cindex));
      task33->add_dep(task34);
      task34->add_dep(task27);
      dedci_->add_task(task34);

      task34->add_dep(task4);

      std::vector<IndexRange> I38_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I38(new Tensor<T>(I38_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor35 = {I23, t2, I38};
      std::shared_ptr<Task35<T>> task35(new Task35<T>(tensor35, cindex));
      task29->add_dep(task35);
      task35->add_dep(task27);
      dedci_->add_task(task35);


      std::vector<std::shared_ptr<Tensor<T>>> tensor36 = {I38, Gamma9};
      std::shared_ptr<Task36<T>> task36(new Task36<T>(tensor36, cindex, this->e0_));
      task35->add_dep(task36);
      task36->add_dep(task27);
      dedci_->add_task(task36);

      task36->add_dep(task4);

      std::vector<IndexRange> I44_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I44(new Tensor<T>(I44_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor37 = {I23, this->v2_, I44};
      std::shared_ptr<Task37<T>> task37(new Task37<T>(tensor37, cindex));
      task29->add_dep(task37);
      task37->add_dep(task27);
      dedci_->add_task(task37);


      std::vector<std::shared_ptr<Tensor<T>>> tensor38 = {I44, Gamma9};
      std::shared_ptr<Task38<T>> task38(new Task38<T>(tensor38, cindex));
      task37->add_dep(task38);
      task38->add_dep(task27);
      dedci_->add_task(task38);

      task38->add_dep(task4);

      std::vector<IndexRange> I30_index = {this->ci_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I30(new Tensor<T>(I30_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor39 = {I22, t2, I30};
      std::shared_ptr<Task39<T>> task39(new Task39<T>(tensor39, cindex));
      task28->add_dep(task39);
      task39->add_dep(task27);
      dedci_->add_task(task39);


      std::vector<IndexRange> I31_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I31(new Tensor<T>(I31_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor40 = {I30, t2, I31};
      std::shared_ptr<Task40<T>> task40(new Task40<T>(tensor40, cindex));
      task39->add_dep(task40);
      task40->add_dep(task27);
      dedci_->add_task(task40);


      std::vector<std::shared_ptr<Tensor<T>>> tensor41 = {I31, Gamma8};
      std::shared_ptr<Task41<T>> task41(new Task41<T>(tensor41, cindex));
      task40->add_dep(task41);
      task41->add_dep(task27);
      dedci_->add_task(task41);

      task41->add_dep(task3);

      std::vector<IndexRange> I33_index = {this->ci_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I33(new Tensor<T>(I33_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor42 = {I22, t2, I33};
      std::shared_ptr<Task42<T>> task42(new Task42<T>(tensor42, cindex));
      task28->add_dep(task42);
      task42->add_dep(task27);
      dedci_->add_task(task42);


      std::vector<IndexRange> I34_index = {this->ci_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I34(new Tensor<T>(I34_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor43 = {I33, this->f1_, I34};
      std::shared_ptr<Task43<T>> task43(new Task43<T>(tensor43, cindex));
      task42->add_dep(task43);
      task43->add_dep(task27);
      dedci_->add_task(task43);


      std::vector<IndexRange> I35_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I35(new Tensor<T>(I35_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor44 = {I34, t2, I35};
      std::shared_ptr<Task44<T>> task44(new Task44<T>(tensor44, cindex));
      task43->add_dep(task44);
      task44->add_dep(task27);
      dedci_->add_task(task44);


      std::vector<std::shared_ptr<Tensor<T>>> tensor45 = {I35, Gamma9};
      std::shared_ptr<Task45<T>> task45(new Task45<T>(tensor45, cindex));
      task44->add_dep(task45);
      task45->add_dep(task27);
      dedci_->add_task(task45);

      task45->add_dep(task4);

      std::vector<IndexRange> I41_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I41(new Tensor<T>(I41_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor46 = {I33, t2, I41};
      std::shared_ptr<Task46<T>> task46(new Task46<T>(tensor46, cindex));
      task42->add_dep(task46);
      task46->add_dep(task27);
      dedci_->add_task(task46);


      std::vector<std::shared_ptr<Tensor<T>>> tensor47 = {I41, Gamma9};
      std::shared_ptr<Task47<T>> task47(new Task47<T>(tensor47, cindex, this->e0_));
      task46->add_dep(task47);
      task47->add_dep(task27);
      dedci_->add_task(task47);

      task47->add_dep(task4);

      std::vector<IndexRange> I47_index = {this->ci_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I47(new Tensor<T>(I47_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor48 = {I33, this->v2_, I47};
      std::shared_ptr<Task48<T>> task48(new Task48<T>(tensor48, cindex));
      task42->add_dep(task48);
      task48->add_dep(task27);
      dedci_->add_task(task48);


      std::vector<std::shared_ptr<Tensor<T>>> tensor49 = {I47, Gamma9};
      std::shared_ptr<Task49<T>> task49(new Task49<T>(tensor49, cindex));
      task48->add_dep(task49);
      task49->add_dep(task27);
      dedci_->add_task(task49);

      task49->add_dep(task4);

      std::shared_ptr<Queue<T>> correction_(new Queue<T>());
      std::vector<IndexRange> I48_index;
      std::shared_ptr<Tensor<T>> I48(new Tensor<T>(I48_index, false));
      std::vector<IndexRange> I49_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I49(new Tensor<T>(I49_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor50 = {I48, t2, I49};
      std::shared_ptr<Task50<T>> task50(new Task50<T>(tensor50, pindex));
      correction_->add_task(task50);


      std::vector<IndexRange> I50_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I50(new Tensor<T>(I50_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor51 = {I49, t2, I50};
      std::shared_ptr<Task51<T>> task51(new Task51<T>(tensor51, pindex));
      task50->add_dep(task51);
      correction_->add_task(task51);


      std::vector<std::shared_ptr<Tensor<T>>> tensor52 = {I50, Gamma2};
      std::shared_ptr<Task52<T>> task52(new Task52<T>(tensor52, pindex));
      task51->add_dep(task52);
      correction_->add_task(task52);

      task52->add_dep(task2);

      std::shared_ptr<Queue<T>> density_(new Queue<T>());
      std::vector<std::shared_ptr<Tensor<T>>> tensor53 = {den1};
      std::shared_ptr<Task53<T>> task53(new Task53<T>(tensor53));
      density_->add_task(task53);

      std::vector<IndexRange> I51_index = {this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I51(new Tensor<T>(I51_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor54 = {den1, I51};
      std::shared_ptr<Task54<T>> task54(new Task54<T>(tensor54, pindex));
      task54->add_dep(task53);
      density_->add_task(task54);


      std::vector<IndexRange> I52_index = {this->active_, this->active_, this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I52(new Tensor<T>(I52_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor55 = {I51, t2, I52};
      std::shared_ptr<Task55<T>> task55(new Task55<T>(tensor55, pindex));
      task54->add_dep(task55);
      task55->add_dep(task53);
      density_->add_task(task55);


      std::vector<IndexRange> I53_index = {this->active_, this->active_, this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I53(new Tensor<T>(I53_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor56 = {I52, t2, I53};
      std::shared_ptr<Task56<T>> task56(new Task56<T>(tensor56, pindex));
      task55->add_dep(task56);
      task56->add_dep(task53);
      density_->add_task(task56);


      std::vector<std::shared_ptr<Tensor<T>>> tensor57 = {I53, Gamma17};
      std::shared_ptr<Task57<T>> task57(new Task57<T>(tensor57, pindex));
      task56->add_dep(task57);
      task57->add_dep(task53);
      density_->add_task(task57);

      task57->add_dep(task5);

      std::vector<IndexRange> I54_index = {this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I54(new Tensor<T>(I54_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor58 = {den1, I54};
      std::shared_ptr<Task58<T>> task58(new Task58<T>(tensor58, pindex));
      task58->add_dep(task53);
      density_->add_task(task58);


      std::vector<IndexRange> I55_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I55(new Tensor<T>(I55_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor59 = {I54, t2, I55};
      std::shared_ptr<Task59<T>> task59(new Task59<T>(tensor59, pindex));
      task58->add_dep(task59);
      task59->add_dep(task53);
      density_->add_task(task59);


      std::vector<IndexRange> I56_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I56(new Tensor<T>(I56_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor60 = {I55, t2, I56};
      std::shared_ptr<Task60<T>> task60(new Task60<T>(tensor60, pindex));
      task59->add_dep(task60);
      task60->add_dep(task53);
      density_->add_task(task60);


      std::vector<std::shared_ptr<Tensor<T>>> tensor61 = {I56, Gamma2};
      std::shared_ptr<Task61<T>> task61(new Task61<T>(tensor61, pindex));
      task60->add_dep(task61);
      task61->add_dep(task53);
      density_->add_task(task61);

      task61->add_dep(task2);

      std::shared_ptr<Queue<T>> density2_(new Queue<T>());
      std::vector<std::shared_ptr<Tensor<T>>> tensor62 = {den2};
      std::shared_ptr<Task62<T>> task62(new Task62<T>(tensor62));
      density2_->add_task(task62);

      std::vector<IndexRange> I57_index = {this->active_, this->active_, this->virt_, this->virt_};
      std::shared_ptr<Tensor<T>> I57(new Tensor<T>(I57_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor63 = {den2, I57};
      std::shared_ptr<Task63<T>> task63(new Task63<T>(tensor63, pindex));
      task63->add_dep(task62);
      density2_->add_task(task63);


      std::vector<IndexRange> I58_index = {this->active_, this->active_, this->active_, this->active_};
      std::shared_ptr<Tensor<T>> I58(new Tensor<T>(I58_index, false));
      std::vector<std::shared_ptr<Tensor<T>>> tensor64 = {I57, t2, I58};
      std::shared_ptr<Task64<T>> task64(new Task64<T>(tensor64, pindex));
      task63->add_dep(task64);
      task64->add_dep(task62);
      density2_->add_task(task64);


      std::vector<std::shared_ptr<Tensor<T>>> tensor65 = {I58, Gamma2};
      std::shared_ptr<Task65<T>> task65(new Task65<T>(tensor65, pindex));
      task64->add_dep(task65);
      task65->add_dep(task62);
      density2_->add_task(task65);

      task65->add_dep(task2);

      return make_tuple(queue_, energy_, dedci_, density_, correction_, density2_);
    };

  public:
    CAS_test(std::shared_ptr<const SMITH_Info> ref) : SpinFreeMethod<T>(ref) {
      this->eig_ = this->f1_->diag();
      t2 = this->v2_->clone();
      e0_ = this->e0();
      this->update_amplitude(t2, this->v2_, true);
      t2->scale(2.0);
      r = t2->clone();
      den1 = this->h1_->clone();
      den2 = this->v2_->clone();
      deci = this->rdm0deriv_->clone();
    };
    ~CAS_test() {};

    void solve() {
      this->print_iteration();
      int iter = 0;
      std::shared_ptr<Queue<T>> queue, energ, dec, dens, correct, dens2;
      for ( ; iter != ref_->maxiter(); ++iter) {
        std::tie(queue, energ, dec, dens, correct, dens2) = make_queue_();
        while (!queue->done())
          queue->next_compute();
        this->update_amplitude(t2, r);
        const double err = r->rms();
        r->zero();
        energy_ = energy(energ);
        this->print_iteration(iter, energy_, err);
        if (err < ref_->thresh()) break;
      }
      this->print_iteration(iter == ref_->maxiter());
      std::cout << " === Calculating CI derivative dE/dcI ===" << std::endl;
      while (!dec->done())
        dec->next_compute();
      deci->print1("CI derivative tensor: ", 1.0e-15);
      std::cout << std::endl;
      std::cout << "CI derivative * cI  = " << std::setprecision(10) <<  deci->dot_product(this->rdm0deriv_) << std::endl;
      std::cout << std::endl;

      std::cout << " === Computing unrelaxed density matrix, dm1, <1|E_pq|1> + 2<0|E_pq|1> ===" << std::endl;
      while (!dens->done())
        dens->next_compute();
#if 0
      den1->print2("smith d1 correlated one-body density matrix", 1.0e-5);
#endif
      correct_den1 = correction(correct);
      std::cout << "Unlinked correction term, <1|1>*rdm1 = " << std::setprecision(10) << correct_den1 << "*rdm1" << std::endl;
      std::cout << " === Computing unrelaxed density matrix, dm2, <0|E_pqrs|1>  ===" << std::endl;
      while (!dens2->done())
        dens2->next_compute();
#if 0
      den2->print4("smith d2 correlated two-body density matrix", 1.0e-5);
#endif
    };

    double energy(std::shared_ptr<Queue<T>> energ) {
      double en = 0.0;
      while (!energ->done()) {
        std::shared_ptr<Task<T>> c = energ->next_compute();
        en += c->energy();
      }
      return en;
    }

    double correction(std::shared_ptr<Queue<T>> correct) {
      double n = 0.0;
      while (!correct->done()) {
        std::shared_ptr<Task<T>> c = correct->next_compute();
        n += c->correction();
      }
      return n;
    }

    std::shared_ptr<const Matrix> rdm1() const { return den1->matrix(); }
    std::shared_ptr<const Matrix> rdm2() const { return den2->matrix2(); }

    double rdm1_correction() const { return correct_den1; }

    std::shared_ptr<const Civec> ci_deriv() const { return deci->civec(this->det_); }

};

}
}
}
#endif

