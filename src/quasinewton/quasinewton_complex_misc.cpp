/* 
 *  The Chronus Quantum (ChronusQ) software package is high-performace 
 *  computational chemistry software with a strong emphasis on explicitly 
 *  time-dependent and post-SCF quantum mechanical methods.
 *  
 *  Copyright (C) 2014-2015 Li Research Group (University of Washington)
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *  
 *  Contact the Developers:
 *    E-Mail: xsli@uw.edu
 *  
 */
#include <quasinewton.h>

namespace ChronusQ {
  template<>
  void QuasiNewton<dcomplex>::Orth(ComplexCMMap &A){
    int N   = A.cols();
    int M   = A.rows();
    int LDA = M;
    int INFO;
    dcomplex * AMAT = A.data();
    dcomplex * TAU = this->LAPACK_SCR;
    this->WORK = TAU + N;

    zgeqrf_(&M,&N,AMAT,&LDA,TAU,this->WORK,&this->LWORK,&INFO);
    zungqr_(&M,&N,&N,AMAT,&LDA,TAU,this->WORK,&this->LWORK,&INFO);
    
  }

  template<>
  void QuasiNewton<dcomplex>::Orth(ComplexCMMatrix &A){
    int N   = A.cols();
    int M   = A.rows();
    int LDA = M;
    int INFO;
    dcomplex * AMAT = A.data();
    dcomplex * TAU = this->LAPACK_SCR;
    this->WORK = TAU + N;

    zgeqrf_(&M,&N,AMAT,&LDA,TAU,this->WORK,&this->LWORK,&INFO);
    zungqr_(&M,&N,&N,AMAT,&LDA,TAU,this->WORK,&this->LWORK,&INFO);
    
  }

  template<>
  void QuasiNewton<dcomplex>::metBiOrth(ComplexCMMap &A, const ComplexCMMatrix &Met){
    int N = A.cols();
    ComplexCMMap AX(this->BiOrthMem,Met.rows(),N);
    AX = Met*A;
    for(auto i = 0; i < N; i++){
      double inner = A.col(i).dot(AX.col(i)).real();
      int sgn = inner / std::abs(inner);
      inner = sgn*std::sqrt(sgn*inner);
      A.col(i) /= inner;
      for(auto j = i + 1; j < N; j++){
        A.col(j) -= A.col(i) * A.col(i).dot(AX.col(j));
      } 
    }
  }

  template<>
  void QuasiNewton<dcomplex>::eigSrt(ComplexCMMap &V, ComplexVecMap &E){
    auto N = V.cols();
    while( N != 0){
      auto newn = 0;
      for(auto i = 1; i < N; i++){
        if( std::abs(E(i-1)) > std::abs(E(i)) ){
          auto tmp = E(i);
          E(i) = E(i-1);
          E(i-1) = tmp;
          V.col(i).swap(V.col(i-1));
          newn = i;
        }
      }
      N = newn;
    }
  }

  template<>
  void QuasiNewton<dcomplex>::initLAPACKScrLen(){
/*
 * (1) Local copy of the real part of the eigenvalues (reused for Tau storage 
 *      for QR)
 *
 * (2) Space for the paired / imaginary part of the eigenvalues
 *
 * (3) Space for imaginary parts of paired eigenvalues
 *
 * (4) Length of LAPACK workspace (used in all LAPACK Calls)
 *
 * (5) Total complex double precision words required for LAPACK
 *
 */
    this->LWORK          = 6*this->N_;
    this->LEN_LAPACK_SCR += this->maxSubSpace_;   // 1
    if(!this->isHermetian_ || this->symmetrizedTrial_)
      this->LEN_LAPACK_SCR += this->maxSubSpace_; // 2
//  if(!this->isHermetian_ && this->symmetrizedTrial_)
//    this->LEN_LAPACK_SCR += 2*this->maxSubSpace_; // 3
    this->LEN_LAPACK_SCR += this->LWORK;          // 4
    this->LenScr += this->LEN_LAPACK_SCR;         // 5

    this->LenRealScr = 2*this->N_;         // RWORK
    this->LenRealScr = this->maxSubSpace_; // Real Eigenvalues
  }
}; // namespace ChronusQ