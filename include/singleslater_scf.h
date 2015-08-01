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
template<typename T>
void SingleSlater<T>::initMemLen(){
  this->lenX_      = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenXp_     = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenF_      = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenP_      = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenCoeff_  = 7;
  this->lenB_      = this->lenCoeff_   * this->lenCoeff_;
  this->LWORK_     = 4 * this->nBasis_ * this->nTCS_;
  this->lenLambda_ = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenDelF_   = this->nBasis_ * this->nBasis_ * this->nTCS_ * this->nTCS_;
  this->lenOccNum_ = this->nBasis_ * this->nTCS_   * this->nTCS_;

  this->lenScr_ = 0;

  this->lenScr_ += this->lenX_;     // Storage for S^(-0.5)
  this->lenScr_ += this->lenF_;     // Storage for Alpha (Total) Fock
  this->lenScr_ += this->lenP_;     // Storage for Alpha (Total) Density
  this->lenScr_ += this->lenCoeff_; // Storage for CDIIS Coefficients
  this->lenScr_ += this->lenB_;     // Storage for CDIIS Metric
  this->lenScr_ += 2*(this->lenCoeff_ - 1) * this->lenF_; // CDIIS Commutator (A) array
  if(!this->isClosedShell) {
    this->lenScr_ += this->lenF_;     // Storage for Beta Fock
    this->lenScr_ += this->lenP_;     // Storage for Beta Density
    this->lenScr_ += 2*(this->lenCoeff_ - 1) * this->lenF_; // CDIIS Commutator (B) array
  }
  if(this->Ref_ == CUHF) {
    this->lenScr_ += this->lenXp_; // Storage for X^(0.5)
    this->lenScr_ += this->lenOccNum_; // Storage for Occupation Numbers (NOs)
    this->lenScr_ += this->lenLambda_; // Storage for Lambda
    this->lenScr_ += this->lenDelF_;   // Stroage for DelF
    this->lenScr_ += this->lenP_;      // Storage for NOs
  }

  this->lenScr_ += this->LWORK_; // LAPACK Scratch space

}; // initMemLen

template <typename T>
void SingleSlater<T>::initSCFPtr(){
  this->SCF_SCR        = NULL;
  this->XMem_          = NULL;
  this->FpAlphaMem_    = NULL;
  this->FpBetaMem_     = NULL;
  this->POldAlphaMem_  = NULL;
  this->POldBetaMem_   = NULL;
  this->ErrorAlphaMem_ = NULL;
  this->ErrorBetaMem_  = NULL;
  this->FADIIS_        = NULL;
  this->FBDIIS_        = NULL;
  this->WORK_          = NULL;
  this->XpMem_         = NULL;
  this->lambdaMem_     = NULL;
  this->delFMem_       = NULL;
  this->PNOMem_        = NULL;
  this->occNumMem_     = NULL;
}; // initSCFPtr

template <typename T>
void SingleSlater<T>::initSCFMem(){
  this->initSCFPtr();
  this->initMemLen();

  T* LAST_FOR_SECTION;
  int LEN_LAST_FOR_SECTION;

  this->SCF_SCR = new double[this->lenScr_];
  std::memset(this->SCF_SCR,0.0,this->lenScr_*sizeof(double));

  this->XMem_          = this->SCF_SCR;
  this->FpAlphaMem_    = this->XMem_          + this->lenX_;
  this->POldAlphaMem_  = this->FpAlphaMem_    + this->lenF_;
  this->ErrorAlphaMem_ = this->POldAlphaMem_  + this->lenP_;
  this->FADIIS_        = this->ErrorAlphaMem_ + this->lenF_*(this->lenCoeff_ -1);
  LAST_FOR_SECTION     = this->FADIIS_;
  LEN_LAST_FOR_SECTION = this->lenF_*(this->lenCoeff_ -1);
  if(!this->isClosedShell){
    this->FpBetaMem_     = LAST_FOR_SECTION + LEN_LAST_FOR_SECTION;
    this->POldBetaMem_   = this->FpBetaMem_    + this->lenF_;
    this->ErrorBetaMem_  = this->POldBetaMem_  + this->lenP_;
    this->FBDIIS_        = this->ErrorBetaMem_ + this->lenF_*(this->lenCoeff_ -1);
    LAST_FOR_SECTION     = this->FBDIIS_;
    LEN_LAST_FOR_SECTION = this->lenF_*(this->lenCoeff_ -1);
  }
  if(this->Ref_ == CUHF) {
    this->XpMem_     = LAST_FOR_SECTION + LEN_LAST_FOR_SECTION;
    this->delFMem_   = this->XpMem_     + this->lenX_;
    this->lambdaMem_ = this->delFMem_   + this->lenDelF_;
    this->PNOMem_    = this->lambdaMem_ + this->lenLambda_;
    this->occNumMem_ = this->PNOMem_    + this->lenP_;
    LAST_FOR_SECTION = this->occNumMem_;
    LEN_LAST_FOR_SECTION = this->lenOccNum_;
  }
  
  this->WORK_ = LAST_FOR_SECTION + LEN_LAST_FOR_SECTION;
}; //initSCFMem

template<typename T>
void SingleSlater<T>::SCF(){
  if(!this->aointegrals_->haveAOOneE) this->aointegrals_->computeAOOneE();
  int iter; 

  this->initSCFMem();
  this->formX();
  for (iter = 0; iter < this->maxSCFIter_; iter++){
    this->fileio_->out << endl << endl << bannerTop <<endl;  
    this->fileio_->out << "SCF iteration:"<< iter+1 <<endl;  
    this->fileio_->out << bannerEnd <<endl;  

    if(this->Ref_ == CUHF) this->formNO();
    this->diagFock();
    this->formDensity();
    this->formFock();

    if(this->Ref_ != CUHF){ // DIIS NYI for CUHF
      this->GenDComm(iter);
      this->CpyFock(iter);   
      if(iter % (this->lenCoeff_-1) == (this->lenCoeff_-2) && iter != 0) this->CDIIS();
    }
    this->evalConver();
    if(this->isConverged) break;

  }; // SCF Loop
  delete [] this->SCF_SCR;

  if(!this->isConverged)
    CErr("SCF Failed to converge within maximum number of iterations",this->fileio_->out);
  this->fileio_->out <<"\n"<<endl; 
  this->fileio_->out << bannerEnd <<endl<<std::fixed;
  this->fileio_->out << "\nRequested convergence on RMS density matrix = " <<std::setw(5)<<this->denTol_ <<"  within  " << this->maxSCFIter_ <<"  cycles."<<endl;
  this->fileio_->out << "Requested convergence on             energy = " <<this->eneTol_ << endl;
  if(this->isConverged){
    this->fileio_->out << endl << "SCF Completed: E(";
    if(this->Ref_ == RHF)  this->fileio_->out << "RHF";
    if(this->Ref_ == UHF)  this->fileio_->out << "UHF";
    if(this->Ref_ == CUHF) this->fileio_->out << "CUHF";
    this->fileio_->out << ") = ";
    this->fileio_->out << this->totalEnergy << "  Eh after  " << iter + 1 << "  SCF Iterations" << endl;
  }
  this->fileio_->out << bannerEnd <<endl;
}
