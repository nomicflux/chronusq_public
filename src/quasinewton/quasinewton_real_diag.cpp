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
  void QuasiNewton<double>::stdHerDiag(int NTrial, ostream &output){
    // Solve E(R)| X(R) > = | X(R) > ω
    char JOBV = 'V';
    char UPLO = 'L';
    int INFO;
    dsyev_(&JOBV,&UPLO,&NTrial,this->XTSigmaRMem,&NTrial,
           this->ERMem,this->WORK,&this->LWORK,&INFO); 
    if(INFO!=0) CErr("DSYEV failed to converge in Davison Iterations",output);
  } // stdHerDiag

  template<>
  void QuasiNewton<double>::symmHerDiag(int NTrial, ostream &output){
    /*
     * Solve S(R)| X(R) > = E(R)| X(R) > (1/ω)
     *
     * | X(R) > = | X(R)_g >
     *            | X(R)_u >
     *
     * The opposite (1/ω vs ω) is solved because the metric is not positive definite
     * and can therefore not be solved using DSYGV because of the involved Cholesky
     * decomposition.
     *
     */ 
    char JOBV = 'V';
    char UPLO = 'L';
    int iType = 1;
    int TwoNTrial = 2*NTrial;
    int INFO;

    RealCMMap SSuper(this->SSuperMem, 2*NTrial,2*NTrial);
    RealCMMatrix SCPY(SSuper); // Copy of original matrix to use for re-orthogonalization

    // Perform diagonalization of reduced subspace using DSYGV
    dsygv_(&iType,&JOBV,&UPLO,&TwoNTrial,this->SSuperMem,&TwoNTrial,
           this->ASuperMem,&TwoNTrial,this->ERMem,this->WORK,&this->LWORK,
           &INFO);
    if(INFO!=0) CErr("DSYGV failed to converge in Davison Iterations",output);
    
    // Grab the "positive paired" roots (throw away other element of the pair)
    this->ERMem += NTrial;
    RealVecMap ER    (this->ERMem,NTrial);
    new (&SSuper) RealCMMap(this->SSuperMem+2*NTrial*NTrial,2*NTrial,NTrial);

    // Swap the ordering because we solve for (1/ω)
    for(auto i = 0 ; i < NTrial; i++) ER(i) = 1.0/ER(i);
    for(auto i = 0 ; i < NTrial/2; i++){
      SSuper.col(i).swap(SSuper.col(NTrial - i - 1));
      double tmp = ER(i);
      ER(i) = ER(NTrial - i - 1);
      ER(NTrial - i - 1) = tmp;
    }

    /*
     * Re-orthogonalize the eigenvectors with respect to the metric S(R)
     * because DSYGV orthogonalzies the vectors with respect to E(R)
     * because we solve the opposite problem.
     *
     * Gramm-Schmidt
     */
/*
    for(auto i = 0; i < NTrial; i++){
      double inner = SSuper.col(i).dot(SCPY*SSuper.col(i));
      int sgn = inner / std::abs(inner);
      inner = sgn*std::sqrt(sgn*inner);
      SSuper.col(i) /= inner;
      for(auto j = i+1; j < NTrial; j++){
        SSuper.col(j) -= 
          SSuper.col(i)*(SSuper.col(i).dot(SCPY*SSuper.col(j)));
      }
    }
*/
    this->metBiOrth(SSuper,SCPY);

    // Separate the eigenvectors into gerade and ungerade parts
    RealCMMap XTSigmaR(this->XTSigmaRMem,NTrial,NTrial);
    RealCMMap XTSigmaL(this->XTSigmaLMem,NTrial,NTrial);
    XTSigmaR = SSuper.block(0,     0,NTrial,NTrial);
    XTSigmaL = SSuper.block(NTrial,0,NTrial,NTrial);
  } // symmHerDiag

  template<>
  void QuasiNewton<double>::diagMem(int NTrial){
    int IOff = NTrial;
    if(!this->isHermetian_ || this->symmetrizedTrial_){
      IOff += NTrial; // Space for paired eigenvalues or imaginary part
    }
    this->ERMem = LAPACK_SCR;
    this->WORK  = this->ERMem + IOff;
  } // diagMem

  /** Diagoanlize Reduced Problem **/
  template<>
  void QuasiNewton<double>::redDiag(int NTrial,ostream &output){
    this->diagMem(NTrial); 
    if(this->isHermetian_) {
      if(!this->symmetrizedTrial_) this->stdHerDiag(NTrial,output);
      else                         this->symmHerDiag(NTrial,output);
    } else {
    
    } 
  } // redDiag

}; // namespace ChronusQ
