#include <basisset.h>

namespace ChronusQ{

  /**
   *  Print the header for BasisSet::printInfo
   */ 
  void BasisSet::printHeader(){
    this->fileio_->out << endl << "Basis Function Information:" << endl << endl;;
  }

  /**
   *  Print BasisSet metadata:
   *    nBasis
   *    nPrimitive
   *    maxPrim
   *    nShell
   *    nLShell
   *    nShellPair
   */ 
  void BasisSet::printMeta(){
    
    this->fileio_->out << "  nBasis      =  " <<  this->nBasis_     << endl; 
    this->fileio_->out << "  nPrimitive  =  " <<  this->nPrimitive_ << endl; 
    this->fileio_->out << "  maxPrim     =  " <<  this->maxPrim_    << endl; 
    this->fileio_->out << "  maxL        =  " <<  this->maxL_       << endl; 
    this->fileio_->out << "  nShell      =  " <<  this->nShell_     << endl; 
     
    for(auto i = 0; i < this->nLShell_.size(); i++){
      this->fileio_->out <<"  n" << HashS(i) << "Shell     =  "<< this->nLShell_[i] << endl;
    }

    this->fileio_->out << "  nShellPair  =  " <<  this->nShellPair_ << endl; 
  }


  /**
   *  Print Basis Set definition
   */ 
  void BasisSet::printBasis(){
    this->fileio_->out.precision(6);
    this->fileio_->out.fill(' ');
    this->fileio_->out.setf(ios::right,ios::adjustfield);
    this->fileio_->out.setf(ios::fixed,ios::floatfield);
    this->fileio_->out << endl << "Cartesian Basis Functions:" << endl;
    this->fileio_->out << endl;
    this->fileio_->out << std::setw(16) << "        Shell Type" << "    Center" << 
      std::setw(8) << "L" << std::setw(26) << "exponent" << std::setw(18) << 
      "coefficient" << endl;
    this->fileio_->out << bannerMid << endl;

    auto iShell = 0;
    for(auto shell : this->shells_){
      this->fileio_->out << std::setw(5)  << iShell + 1;
      this->fileio_->out << std::setw(8)  << HashS(shell.contr[0].l);
      this->fileio_->out << std::setw(13) << this->mapSh2Cen_[iShell] << "  "; 
      this->fileio_->out << std::setw(8)  << shell.contr[0].l;
 
      for(auto iPrim = 0; iPrim < shell.alpha.size(); iPrim++){
        if(iPrim != 0) this->fileio_->out << std::setw(36) << " ";

        this->fileio_->out << std::setw(26) << shell.alpha[iPrim];
        this->fileio_->out << std::setw(18) << shell.contr[0].coeff[iPrim];
        this->fileio_->out << endl;
      }

      this->fileio_->out << endl;
      iShell++;
    }
  }

  /**
   *  Print important information about a BasisSet object
   */ 
  void BasisSet::printInfo(){
    this->printHeader();
    this->printMeta();
    this->printBasis();
  }
} // namespace ChronusQ

