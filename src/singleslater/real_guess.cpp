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
#include <singleslater.h>
#include <aointegrals.h>
#include <basisset.h>
#include <workers.h>
#ifdef USE_LIBINT
using ChronusQ::BasisSet;
using ChronusQ::Controls;
using ChronusQ::Molecule;
using ChronusQ::HashNAOs;
namespace ChronusQ {
//--------------------------------//
// form the initial guess of MO's //
//--------------------------------//
template<>
void SingleSlater<double>::formGuess() {
  
  std::vector<RealMatrix> atomMO;
  std::vector<RealMatrix> atomMOB;
  int readNPGTO,L, nsize;
  this->moA_->setZero();
  if(this->Ref_ != RHF) this->moB_->setZero();
  this->haveMO = true;
/*
  // Determining unique atoms
  std::vector<Atoms> uniqueElement;
  std::vector<int>   repeatedAtoms;
  for(auto iAtm = 0; iAtm < this->molecule_->nAtoms(); iAtm++){
    if(iAtm == 0){ 
      uniqueElement.push_back(elements[this->molecule_->index(iAtm)]);
      repeatedAtoms.push_back(iAtm);
    }
    int uSize = uniqueElement.size();
    bool uniq = true;
    int count;
    for(auto iUn = 0; iUn < uSize; iUn++){
      if(uniqueElement[iUn].atomicNumber == 
        elements[this->molecule_->index(iAtm)].atomicNumber){
        uniq = false;
	count=iUn;
        break;
      }
    }
    if(uniq) {
      uniqueElement.push_back(elements[this->molecule_->index(iAtm)]);
      repeatedAtoms.push_back(uniqueElement.size()-1);
    }
    else {
      if (iAtm!=0)
        repeatedAtoms.push_back(count); 
    }
  }

  this->fileio_->out << "Found " << uniqueElement.size() << 
                        " unique atoms in molecule" << endl;
  
  this->fileio_->out << endl << "Atomic SCF Starting............." << endl << endl;
  for(auto iUn = 0; iUn < uniqueElement.size(); iUn++){
    auto aointegralsAtom  = new AOIntegrals;
    auto hartreeFockAtom  = new SingleSlater<double>;
    auto controlAtom      = new Controls;
    auto basisSetAtom     = new BasisSet;
    auto dfBasissetAtom   = new BasisSet;
    std::vector<libint2::Shell> atomShell;
    Molecule uniqueAtom(uniqueElement[iUn],this->fileio_);
    uniqueAtom.readCharge(0);
    uniqueAtom.readMultip(uniqueElement[iUn].defaultMult);

    basisSetAtom = this->basisset_->constructExtrn(&uniqueAtom); 
    basisSetAtom->makeMapSh2Bf();
    basisSetAtom->makeMapSh2Cen(&uniqueAtom);
    auto nsize = basisSetAtom->nBasis();

    RealMatrix denMOA(nsize, nsize);
    RealMatrix denMOB(nsize, nsize);
    controlAtom->iniControls();
    controlAtom->doCUHF = true;
    aointegralsAtom->iniAOIntegrals (&uniqueAtom, basisSetAtom, this->fileio_, controlAtom, dfBasissetAtom);
    hartreeFockAtom->iniSingleSlater(&uniqueAtom, basisSetAtom, aointegralsAtom, this->fileio_, controlAtom);
    hartreeFockAtom->moA_->setZero();
    if (hartreeFockAtom->Ref_ != RHF) hartreeFockAtom->moB_->setZero();
    hartreeFockAtom->haveMO = true;
    cout << this << endl << hartreeFockAtom << endl << basisSetAtom << endl;
    cout << "HERE" << endl;
    hartreeFockAtom->formFock();
    cout << "HERE" << endl;
    hartreeFockAtom->computeEnergy();
    cout << "HERE" << endl;
    hartreeFockAtom->SCF();
    cout << "HERE" << endl;
    if (hartreeFockAtom->Ref_ != RHF){
      denMOB = (*hartreeFockAtom->densityB_);
      denMOA = (*hartreeFockAtom->densityA_);
    }
    else{
      denMOA = (*hartreeFockAtom->densityA_);
      denMOB = (*hartreeFockAtom->densityA_);
    }
    atomMO.push_back(denMOA);
    atomMOB.push_back(denMOB);
  //basisSetAtom->setnBasis(0);
  //basisSetAtom->setnPrimitive(0);
  }
  this->fileio_->out << endl << "Atomic SCF Completed............." << endl << endl;
  int n = (*this->moA_).rows();
  int lenX  = n * n;
  int lenFp = n * n;
  int lenFb = n * n;
  int lwork = 4 *n;
  int lenoccNum = n;
  int lenScr    = lenX + lenFp + lenFb + lwork + lenoccNum;
  double *SCR, *Xmem, *Fpmem, *Fbmem, *work, *occNum;
  
  SCR   = new double[lenScr];
  Xmem  = SCR;
  Fpmem = Xmem  + lenX;
  Fbmem = Fpmem + lenFp;
  work  = Fbmem + lenFb;
  occNum= work  + lwork;
 
  RealMap X(Xmem, n, n);
  RealMap FpAlpha(Fpmem, n, n);
  RealMap FpBeta (Fbmem, n, n);
  for(auto iUn = 0; iUn < uniqueElement.size(); iUn++){
    Molecule uniqueAtom(uniqueElement[iUn],this->fileio_);
  }
  this->haveMO = true;
  if(!this->aointegrals_->haveAOOneE) this->aointegrals_->computeAOOneE();
  X=(*this->aointegrals_->overlap_).pow(-0.5);
  int nIndex=0;
  for (auto k=0; k<repeatedAtoms.size();k++){
    for (auto i=nIndex; i<atomMO[repeatedAtoms[k]].rows()+nIndex;i++){
      for (auto j=nIndex; j<atomMO[repeatedAtoms[k]].cols()+nIndex;j++){
	(*this->densityA_)(i,j)=((atomMO[repeatedAtoms[k]])(i-nIndex,j-nIndex)+(atomMOB[repeatedAtoms[k]])(i-nIndex,j-nIndex))/2;         
        if (this->Ref_ != RHF){
	  (*this->densityB_)(i,j)=((atomMO[repeatedAtoms[k]])(i-nIndex,j-nIndex)+(atomMOB[repeatedAtoms[k]])(i-nIndex,j-nIndex))/2;         
	}
      }
    }
    nIndex = nIndex+atomMO[repeatedAtoms[k]].rows();
  }
  atomMO.resize(0);
  atomMOB.resize(0);
  
  if(this->Ref_ != RHF){
    int numE = this->molecule_->nTotalE();
    int betaE  = (numE-this->molecule_->multip()-1)/2;
    int alphaE = (numE - betaE);
    (*this->densityA_) =2* (double)alphaE/(double)numE * (*this->densityA_);
    (*this->densityB_) =2* (double)betaE/(double)numE * (*this->densityB_);
  }
  int info  = -1;
  char j = 'V';
  char u = 'U';
  this->haveDensity = true;
  this->formFock();
  FpAlpha   = X.transpose()*(*this->fockA_)*X;
  if(this->Ref_ != RHF) {
    FpBeta     = X.transpose()*(*this->fockB_)*X;
  }
  dsyev_(&j,&u,&n, FpAlpha.data(), &n, this->epsA_->data(), work, &lwork, &info);
  FpAlpha.transposeInPlace(); // bc Row Major
  (*this->moA_) = X*FpAlpha;
  
  if(this->Ref_ != RHF) {
    dsyev_(&j,&u,&n, FpBeta.data(), &n, this->epsB_->data(), work, &lwork, &info);
    FpBeta.transposeInPlace(); // bc Row Major
    (*this->moB_) = X*FpBeta;
  }

  this->haveDensity = false;
  if(this->controls_->printLevel>=3) {
    prettyPrint(this->fileio_->out,(*this->moA_),"Alpha MO Coeff");
    if(this->Ref_ != RHF) prettyPrint(this->fileio_->out,(*this->moB_),"Beta MO Coeff");
  };
  delete [] SCR;
*/
};
//------------------------------------------//
// form the initial guess of MOs from input //
//------------------------------------------//
template<>
void SingleSlater<double>::readGuessIO() {
  int i,j;
  this->fileio_->in.clear();
  std::string readString;
  this->fileio_->in.seekg(0,ios::beg);
  this->fileio_->in>>readString;
  readString=stringupper(readString);
  while(!this->fileio_->in.eof()&&readString.compare("$GUESS")) {
    this->fileio_->in>>readString;
    readString=stringupper(readString);
  };
  this->fileio_->in >> readString;
  for(i=0;i<this->nBasis_;i++) for(j=0;j<this->nBasis_;j++){
    this->fileio_->in>>(*(this->moA_))(j,i);
  };
  this->fileio_->in.close();
  if(this->controls_->printLevel>=3) {
    prettyPrint(this->fileio_->out,(*this->moA_),"Alpha MO Coeff");
    if(this->Ref_ != RHF) prettyPrint(this->fileio_->out,(*this->moB_),"Beta MO Coeff");
  };
  this->haveMO = true;
};
//-----------------------------------------------------------------------//
// form the initial guess of MOs from Gaussian raw matrix element file   //
//-----------------------------------------------------------------------//
template<>
void SingleSlater<double>::readGuessGauMatEl(GauMatEl& matEl){
  this->fileio_->out << "Reading MO coefficients from " <<matEl.fname()<< endl;
  if(matEl.nBasis()!=this->nBasis_) CErr("Basis Set mismatch",this->fileio_->out);
  double *scr = matEl.readRec(GauMatEl::moa); 
  for(auto i = 0; i < this->nBasis_*this->nBasis_; i++)
    this->moA_->data()[i] = scr[i];
  this->moA_->transposeInPlace(); // Row Major
  delete [] scr;
  if(this->Ref_ != RHF) {
    scr = matEl.readRec(GauMatEl::mob); 
    for(auto i = 0; i < this->nBasis_*this->nBasis_; i++)
      this->moB_->data()[i] = scr[i];
    this->moB_->transposeInPlace(); // Row Major
    delete [] scr;
  }
  this->matchord();
  if(this->controls_->printLevel>=3) {
    prettyPrint(this->fileio_->out,(*this->moA_),"Alpha MO Coeff");
    if(this->Ref_ != RHF) prettyPrint(this->fileio_->out,(*this->moB_),"Beta MO Coeff");
  };
  this->haveMO = true;
}
//-----------------------------------------------------------------------//
// form the initial guess of MOs from Gaussian formatted checkpoint file //
//-----------------------------------------------------------------------//
template<>
void SingleSlater<double>::readGuessGauFChk(std::string &filename) {
  this->fileio_->out<<"Reading formatted checkpoint file "<<filename<<endl;
  std::string readString;
  int i,j,nBasis;
  double data;
  std::unique_ptr<ifstream> fchk(new ifstream(filename));
  if(fchk->fail()) 
    CErr("Could not find "+filename,this->fileio_->out);

  *fchk>>readString;
  while((!(fchk->eof()))&&(readString.compare("basis"))) *fchk>>readString;
  if(!readString.compare("basis")) {
    *fchk>>readString;
    *fchk>>readString;
    *fchk>>nBasis;
    if(nBasis!=this->nBasis_) {
      this->fileio_->out<<"Basis set mismatch! "<<nBasis<<"!="<<this->nBasis_<<endl;
      exit(1);
    };
  } else {
    this->fileio_->out<<"No basis set found in the formatted checkpoint file! "<<endl;
  };

  while(!(fchk->eof())&&readString.compare("MO")) *fchk>>readString;
  if(!readString.compare("MO")) {
    *fchk>>readString;
    *fchk>>readString;
    *fchk>>readString;
    *fchk>>readString;
    for(i=0;i<nBasis;i++) 
      for(j=0;j<nBasis;j++){
        *fchk>>data;
        (*(this->moA_))(j,i) = data;
    };
  } else {
    this->fileio_->out<<"No basis set found in the formatted checkpoint file! "<<endl;
  };

  fchk->close();
  if(this->controls_->printLevel>=3) {
    prettyPrint(this->fileio_->out,(*this->moA_),"Alpha MO Coeff");
    if(this->Ref_ != RHF) prettyPrint(this->fileio_->out,(*this->moB_),"Beta MO Coeff");
  };
  this->haveMO = true;
};
}; //namespace ChronusQ
#endif
