//
// Author: Hai-Anh Le <anh@u.northwestern.edu>
// Date: January 31, 2014
//


#include "radial.h"
#include "test.h"
//#include "src/integral/carsphlist.h"

double overlap_ss(const std::shared_ptr<CartesianGauss> gA, const std::shared_ptr<CartesianGauss> gB) {

  const int max_iter = 100;
  const double thresh_int = 10e-5;
  double overlapss;

  for (int i = 0; i != 3; ++i) {
    std::tuple<int, std::shared_ptr<CartesianGauss>, std::shared_ptr<CartesianGauss>> gP(i, gA, gB);
    Radial_Int<GaussianProduct, std::tuple<int, std::shared_ptr<CartesianGauss>, std::shared_ptr<CartesianGauss>>> overlap(max_iter, thresh_int, gP);
    ((i == 0) ? overlapss = 2.0 * overlap.integral() : overlapss *= 2.0 * overlap.integral());
  }

  return overlapss;

}

using namespace std;

int main() {

// Test Bessel function
  const double x = 1.2e-4;
  const double sbessel = boost::math::sph_bessel(0, x) * std::exp(-x);
  Modified_Spherical_Bessel_Iexp msbessel(0);
  cout << "                             x = " << setw(20) << setprecision(12) << x << endl;
  cout << "boost:sph_bessel               = " << setw(20) << setprecision(12) << sbessel << endl;
  cout << "Modified_Spherical_Bessel_Iexp = " << setw(20) << setprecision(12) << msbessel.compute(x).toDouble() << endl;
  cout << endl;
  // Boost can only do very small x

#if 0
  cout << " Expansion of a Gaussian about a different centre " << endl;
  BesselI besselI;
  int l = 0;
  const double x =0.1;
  cout << "I_n(x) where n = " << l << " and x = " << x << " is   " << besselI.besseln(l, x) << endl;

  SH sh;
  const int m = 0;
  cout << "(l m x) = (" << l << "  " << m << "  " << x << ")   P_lm(x) =  " << sh.alegendre(l, fabs(m), x) << endl;
  const double phi = 1.3;
  const double theta = 3.1;
  cout << "th = " << theta << "  ph = " << phi << "  Y_lm(x) = " << sh.ylm(l, m, theta, phi).real() << "    " << sh.ylm(l, m, theta, phi).imag() << endl;
#endif

#if 0
  GaussOntoSph gos;
  cout << "coef =   " << gos.compute_c(2, 0, 2, 0, 0) << endl;

  std::list<std::shared_ptr<CartesianGauss>> gauss;
  std::array<double, 3> centre = {0.0, 0.0, 0.0};
  gauss = gos.sphcar(centre, 0,0);
  cout << "No. of Cartesian Gaussians = " << gauss.size() << endl;
  for (auto& it : gauss) {
    cout << setw(17) << setprecision(9) << it->angular_momentum(0) << " ";
    cout << setw(17) << setprecision(9) << it->angular_momentum(1) << " ";
    cout << setw(17) << setprecision(9) << it->angular_momentum(2) << endl;
  }
  for (auto& it : gauss) {
    cout << "Centre of Gaussian =  " << endl;
    for (int i = 0; i != 3; ++i) {
      cout << setw(17) << setprecision(9) << it->centre(i) << "   ";
    }
    cout << endl;
  }
#endif

#if 0
const int maxl = 3;
for (int iz = 0; iz <= maxl; ++iz) {
  for (int iy = 0; iy <= maxl - iz; ++iy) {
    const int ix = maxl - iz - iy;
    Comb comb;
    std::array<int, 3> cartesian = {ix, iy, iz};
    std::shared_ptr<CarSph> carsph = std::make_shared<CarSph>(cartesian);
    carsph->transform_CarSph();
    carsph->print();
    cout << "---" << endl;
  }
}
#endif

#if 1
  std::array<double, 3> centreB = {0.0000, 0.0000, 0.0000};
  std::array<int, 2> lm = {0, 0};
  std::shared_ptr<RealSH> rsh = std::make_shared<RealSH>(lm, centreB);
  rsh->print();

  std::array<double, 3> centreA = {0.0000, 0.0000, 0.5000};
  std::array<int, 3> angular_momentumA = {0, 2, 0};
  const double alphaA = 1.0;
  std::shared_ptr<CartesianGauss> cargaussA = std::make_shared<CartesianGauss>(alphaA, angular_momentumA, centreA);
  cargaussA->print();

  std::array<double, 3> centreC = {0.0000, 0.0000, 0.0000};
  std::array<int, 3> angular_momentumC = {2, 0, 0};
  const double alphaC = 1.0;
  std::shared_ptr<CartesianGauss> cargaussC = std::make_shared<CartesianGauss>(alphaC, angular_momentumC, centreC);
  cargaussC->print();

  const double r = 1.0;

  std::shared_ptr<ProjectionInt> projAB = std::make_shared<ProjectionInt>(cargaussA, rsh);
  const double int1 = projAB->compute(r);
  cout << " < phi_A | lm_B >(r)  =  " << int1 << endl;

  std::shared_ptr<ProjectionInt> projCB = std::make_shared<ProjectionInt>(cargaussC, rsh);
  const double int2 = projCB->compute(r);
  cout << " < phi_C | lm_B >(r)  =  " << int2 << endl;

  cout << endl;
  cout << " < phi_A | lm_B > < lm_B | phi_C >(r) =  " << int1 * int2 << endl;
#endif

#if 0
  const int lp = 3;
  for (int i = 0; i <= 2*lp; ++i) {
    const int mp = i - lp;
    std::array<int, 2> lmp = {lp, mp};
    std::shared_ptr<SphUSP> sphusp = std::make_shared<SphUSP>(lmp);

//  sphusp->print();

  }
  cout << "***  TEST INTEGRATION ***" << endl;
  std::array<int, 3> ijk = {1, 4, 2};
  std::pair<int, int> lm1 = std::make_pair(4, 2);
  std::pair<int, int> lm2 = std::make_pair(3, 1);
  const double ans = projAB.integrate2SH1USP(lm1, lm2, ijk);
  cout << "int_(lm1 * lm2 * xyz) = " << ans << endl;
#endif

  const int max_iter = 100;
  const double thresh_int = 10e-5;
  const double exp = 2.0;
  const double pi = static_cast<double>(atan(1.0) * 4.0);
  const int nkl = -2;
  const double zeta = 1.0;

#if 0
  cout << " Test Radial Integration " << endl;
  Radial_Int<Gaussian_Int, const double> radial(max_iter, thresh_int, exp);
  cout << "Analytic = " << std::sqrt(pi / exp) / 2.0 << endl;
#endif

#if 0
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projs(projAB, projCB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecp(max_iter, thresh_int, projs);
#endif

#if 1
  std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> ecpABfBC(nkl, zeta, projAB, projCB);
  Radial_Int<ECP_Type2, std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpT2(max_iter, thresh_int, ecpABfBC);
#endif

#if 0
  cout << "**** TEST int <p| 00><00 |s>(r)" << endl;

  cout << "int <100|00><00|000>(r) dr" << endl;
  std::array<int, 3> angular_momentumAx = {1, 0, 0};
  std::shared_ptr<CartesianGauss> cargaussAx = std::make_shared<CartesianGauss>(alphaA, angular_momentumAx, centreA);
  std::shared_ptr<ProjectionInt> projAxB = std::make_shared<ProjectionInt>(cargaussAx, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAxBC(projAxB, projCB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAxBC(max_iter, thresh_int, projAxBC);

  cout << "int <010|00><00|000>(r) dr" << endl;
  std::array<int, 3> angular_momentumAy = {0, 1, 0};
  std::shared_ptr<CartesianGauss> cargaussAy = std::make_shared<CartesianGauss>(alphaA, angular_momentumAy, centreA);
  std::shared_ptr<ProjectionInt> projAyB = std::make_shared<ProjectionInt>(cargaussAy, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAyBC(projAyB, projCB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAyBC(max_iter, thresh_int, projAyBC);

  cout << "int <001|00><00|000>(r) dr" << endl;
  std::array<int, 3> angular_momentumAz = {0, 0, 1};
  std::shared_ptr<CartesianGauss> cargaussAz = std::make_shared<CartesianGauss>(alphaA, angular_momentumAz, centreA);
  std::shared_ptr<ProjectionInt> projAzB = std::make_shared<ProjectionInt>(cargaussAz, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAzBC(projAzB, projCB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAzBC(max_iter, thresh_int, projAzBC);
#endif

#if 0
  cout << "**** TEST int <p| 00><00 |p>(r)" << endl;

  cout << "int <100|00><00|100>(r) dr" << endl;
  std::array<int, 3> angular_momentumCx = {1, 0, 0};
  std::shared_ptr<CartesianGauss> cargaussCx = std::make_shared<CartesianGauss>(alphaC, angular_momentumCx, centreC);
  std::shared_ptr<ProjectionInt> projCxB = std::make_shared<ProjectionInt>(cargaussCx, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAxBCx(projAxB, projCxB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAxBCx(max_iter, thresh_int, projAxBCx);

  cout << "int <010|00><00|010>(r) dr" << endl;
  std::array<int, 3> angular_momentumCy = {0, 1, 0};
  std::shared_ptr<CartesianGauss> cargaussCy = std::make_shared<CartesianGauss>(alphaC, angular_momentumCy, centreC);
  std::shared_ptr<ProjectionInt> projCyB = std::make_shared<ProjectionInt>(cargaussCy, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAyBCy(projAyB, projCyB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAyBCy(max_iter, thresh_int, projAyBCy);

  cout << "int <001|00><00|001>(r) dr" << endl;
  std::array<int, 3> angular_momentumCz = {0, 0, 1};
  std::shared_ptr<CartesianGauss> cargaussCz = std::make_shared<CartesianGauss>(alphaC, angular_momentumCz, centreC);
  std::shared_ptr<ProjectionInt> projCzB = std::make_shared<ProjectionInt>(cargaussCz, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAzBCz(projAzB, projCzB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAzBCz(max_iter, thresh_int, projAzBCz);

  //off-diagonal
  // xy
  cout << "int <100|00><00|010>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAxBCy(projAxB, projCyB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAxBCy(max_iter, thresh_int, projAxBCy);
  cout << "int <010|00><00|100>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAyBCx(projAyB, projCxB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAyBCx(max_iter, thresh_int, projAyBCx);

  //yz
  cout << "int <010|00><00|001>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAyBCz(projAyB, projCzB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAyBCz(max_iter, thresh_int, projAyBCz);
  cout << "int <001|00><00|010>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAzBCy(projAzB, projCyB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAzBCy(max_iter, thresh_int, projAzBCy);

  //zx
  cout << "int <001|00><00|100>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAzBCx(projAzB, projCxB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAzBCx(max_iter, thresh_int, projAzBCx);
  cout << "int <100|00><00|001>(r) dr" << endl;
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAxBCz(projAxB, projCzB);
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAxBCz(max_iter, thresh_int, projAxBCz);
#endif

#if 0
  cout << "TEST int <p| (|10><10| + |11><11| + |1-1><1-1|) p>(r) dr" << endl;
  cout << "int <p | 10><10 | p>(r) dr" << endl;
  std::array<int, 2> lm1 = {1, 0};
  std::shared_ptr<RealSH> rsh1 = std::make_shared<RealSH>(lm1, centreB);
  std::shared_ptr<ProjectionInt> projAB10 = std::make_shared<ProjectionInt>(cargaussA, rsh1);
  std::shared_ptr<ProjectionInt> projCB10 = std::make_shared<ProjectionInt>(cargaussC, rsh1);
//std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB10C(projAB10, projCB10);
//Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB10C(max_iter, thresh_int, projAB10C);
  std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB10C(nkl, zeta, projAB10, projCB10);
  Radial_Int<ECP_Type2, std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB10C(max_iter, thresh_int, projAB10C);

  cout << "int <p | 11><11 | p>(r) dr" << endl;
  std::array<int, 2> lm2 = {1, 1};
  std::shared_ptr<RealSH> rsh2 = std::make_shared<RealSH>(lm2, centreB);
  std::shared_ptr<ProjectionInt> projAB11 = std::make_shared<ProjectionInt>(cargaussA, rsh2);
  std::shared_ptr<ProjectionInt> projCB11 = std::make_shared<ProjectionInt>(cargaussC, rsh2);
//std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB11C(projAB11, projCB11);
//Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB11C(max_iter, thresh_int, projAB11C);
  std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB11C(nkl, zeta, projAB11, projCB11);
  Radial_Int<ECP_Type2, std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB11C(max_iter, thresh_int, projAB11C);

  cout << "int <p | 1-1><1-1 | p>(r) dr" << endl;
  std::array<int, 2> lm3 = {1, -1};
  std::shared_ptr<RealSH> rsh3 = std::make_shared<RealSH>(lm3, centreB);
  std::shared_ptr<ProjectionInt> projAB1m1 = std::make_shared<ProjectionInt>(cargaussA, rsh3);
  std::shared_ptr<ProjectionInt> projCB1m1 = std::make_shared<ProjectionInt>(cargaussC, rsh3);
//std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB1m1C(projAB1m1, projCB1m1);
//Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB1m1C(max_iter, thresh_int, projAB1m1C);
  std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projAB1m1C(nkl, zeta, projAB1m1, projCB1m1);
  Radial_Int<ECP_Type2, std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpAB1m1C(max_iter, thresh_int, projAB1m1C);

  cout << "Answer = " << (ecpAB10C.integral() + ecpAB11C.integral() + ecpAB1m1C.integral()) << endl;
#endif

#if 1
  cout << "TEST int <d| (|22><22| + |21><21| + |20><20| + |2-1><2-1| + |2-2><2-2|) d>(r) dr" << endl;

  for (int lxA = 0; lxA <= 2; ++lxA) {
    for (int lyA = 2 - lxA; lyA >= 0; --lyA) {
      for (int lxC = 0; lxC <= 2; ++lxC) {
        for (int lyC = 2 - lxC; lyC >= 0; --lyC) {
          int lzC = 2 - lxC - lyC;
          int lzA = 2 - lxA - lyA;
//        cout << " dA = (" << lxA << ", " << lyA << ", " << lzA << "); dC = (" << lxC << ", " << lyC << ", " << lzC << ")" << endl;
          std::array<int, 3> lA = {lxA, lyA, lzA};
          std::array<int, 3> lC = {lxC, lyC, lzC};
          std::shared_ptr<CartesianGauss> gA = std::make_shared<CartesianGauss>(alphaA, lA, centreA);
          std::shared_ptr<CartesianGauss> gC = std::make_shared<CartesianGauss>(alphaC, lC, centreC);
          double int_dd = 0.0;
          std::array<int, 2> lmd = {2, 0};
          for (int i = 0; i <= 4; ++i) {
            lmd[1] = i - 2;
            std::shared_ptr<RealSH> rshd = std::make_shared<RealSH>(lmd, centreB);
            std::shared_ptr<ProjectionInt> projABd = std::make_shared<ProjectionInt>(gA, rshd);
            std::shared_ptr<ProjectionInt> projCBd = std::make_shared<ProjectionInt>(gC, rshd);
//          std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projABdC(projABd, projCBd);
//          Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpABdC(max_iter, thresh_int, projABdC);
//          cout << "<" << lxA << lyA << lzA << "|" << lmd[0] << lmd[1] << "><" << lmd[0] << lmd[1] << "|" << lxC << lyC << lzC << "> = " << ecpABdC.integral() << endl;
            std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projABdC(nkl, zeta, projABd, projCBd);
            Radial_Int<ECP_Type2, std::tuple<int, double, std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpABdC(max_iter, thresh_int, projABdC);
            int_dd += ecpABdC.integral();
          }
//        cout << "<d_A|2m_B><2m_B|d_C> = " << int_dd << endl;
          cout << "\\\\  \\braket{" << lxA << lyA << lzA << "_A | 2m_B}\\braket{2m_B | " << lxC << lyC << lzC << "_C} &= " << int_dd << endl;

//        const double overlapdd = overlap_ss(gA, gC);
//        cout << "NA NC <dA|dC> = " << overlapdd << endl;
//        cout << "\\\\  \\braket{" << lxA << lyA << lzA << " | " << lxC << lyC << lzC << "} &= " << overlapdd << endl;
        }
      }
    }
  }

#endif

#if 0
  cout << "TEST int <200 - 020 | 22><22 | 200 - 020 >(r)" << endl;
  std::array<int, 3> angular_momentumAp = {0, 2, 0};
  std::shared_ptr<CartesianGauss> cargaussAp = std::make_shared<CartesianGauss>(alphaA, angular_momentumAp, centreA);
  std::shared_ptr<ProjectionInt> projApB = std::make_shared<ProjectionInt>(cargaussAp, rsh);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projApBAp(projApB, projApB);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projABA(projAB, projAB);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projApBA(projApB, projAB);
  std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>> projABAp(projAB, projApB);
  cout << "int <200 | 22><22 | 200>(r) dr" << endl;
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpABA(max_iter, thresh_int, projABA);
  cout << "int <020 | 22><22 | 020>(r) dr" << endl;
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpApBAp(max_iter, thresh_int, projApBAp);
  cout << "int <020 | 22><22 | 200>(r) dr" << endl;
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpApBA(max_iter, thresh_int, projApBA);
  cout << "int <200 | 22><22 | 020>(r) dr" << endl;
  Radial_Int<Projection2, std::pair<std::shared_ptr<ProjectionInt>, std::shared_ptr<ProjectionInt>>> ecpABAp(max_iter, thresh_int, projABAp);
  cout << " Answer = " << endl;
  cout << ecpABA.integral() - ecpApBA.integral() - ecpABAp.integral() + ecpApBAp.integral() << endl;
#endif

#if 0
  std::pair<std::shared_ptr<CartesianGauss>, std::shared_ptr<RealSH>> gsh(cargaussC, rsh);
  Radial_Int<ABBB_ss, std::pair<std::shared_ptr<CartesianGauss>, std::shared_ptr<RealSH>>> test_ss(max_iter, thresh_int, gsh);
#endif

  // check normalization ss
#if 0
  std::tuple<int, std::shared_ptr<CartesianGauss>, std::shared_ptr<CartesianGauss>> gproduct(0, cargaussA, cargaussA);
  Radial_Int<GaussianProduct, std::tuple<int, std::shared_ptr<CartesianGauss>, std::shared_ptr<CartesianGauss>>> norm(max_iter, thresh_int, gproduct);
  cout << "Should be " << std::pow(2.0 / pi, 1.5) * std::pow(std::sqrt(pi / 2.0), 3.0) << endl;
#endif

#if 0
  const double overlap = overlap_ss(cargaussA, cargaussA);
  cout << "Overlap Integral < phi_A | phi_A > = " << overlap << endl;
#endif

  return 0;

}

