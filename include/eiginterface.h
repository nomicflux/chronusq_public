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
#ifndef EIGINTER_INC
#define EIGINTER_INC
//----------------//
//String constants//
//----------------//
const std::string bannerTop="--------------------------------------------------------------------------------";
const std::string bannerMid="--------------------------------------------------------------------------------";
const std::string bannerEnd="--------------------------------------------------------------------------------";
const auto PRINT_SMALL = 1e-10;


namespace Eigen {
  template<typename Derived>
  void prettyPrint(std::ostream & output, const Derived& m, std::string str){
  int list = 5;
  int i,j,k,n,end,endLT;
  output.precision(10);
  output.fill(' ');
  output.setf(std::ios::right,std::ios::scientific);
  output.setf(std::ios::fixed,std::ios::floatfield);
  output << std::endl << str + ": " << std::endl;
  output << bannerTop;

  for(i=0;i<m.cols();i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= m.cols()) end = m.cols() - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < m.rows(); j++) {
      output << std::setw(5) << std::left << j+1;
//    for(n=i;n<i+end;n++) output<<std::setw(15)<<m.data()[j*m.rows()+n]; // n in the column index (dbwy)
      for(n = i; n < i+end; n++) {
        if(std::abs(m(j,n)) > PRINT_SMALL)
          output << std::setw(15) << std::right << m(j,n); // n in the column index (dbwy)
        else
          output << std::setw(15) << std::right << std::abs(m(j,n)); // n in the column index (dbwy)
      }
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  }

  template<typename Derived>
  void prettyPrintComplex(std::ostream & output, const Derived& m, std::string str){
  int list = 5;
  int i,j,k,n,end,endLT;
  output.precision(10);
  output.fill(' ');
  output.setf(std::ios::right,std::ios::scientific);
  output.setf(std::ios::fixed,std::ios::floatfield);
  output << std::endl << "Re["<< str + "] : " << std::endl;
  output << bannerTop;

  for(i=0;i<m.cols();i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= m.cols()) end = m.cols() - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < m.rows(); j++) {
      output << std::setw(5) << std::left << j+1;
//    for(n=i;n<i+end;n++) output<<std::setw(15)<<m.data()[j*m.rows()+n]; // n in the column index (dbwy)
      for(n = i; n < i+end; n++) {
        if(std::abs(m(j,n).real()) > PRINT_SMALL)
          output << std::setw(15) << std::right << m(j,n).real(); // n in the column index (dbwy)
        else
          output << std::setw(15) << std::right << std::abs(m(j,n).real()); // n in the column index (dbwy)
      }
      output << std::endl;
    };
  };
  output << bannerMid << std::endl;;
  output << std::endl << "Im["<< str + "] : " << std::endl;
  output << bannerTop;

  for(i=0;i<m.cols();i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= m.cols()) end = m.cols() - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < m.rows(); j++) {
      output << std::setw(5) << std::left << j+1;
//    for(n=i;n<i+end;n++) output<<std::setw(15)<<m.data()[j*m.rows()+n]; // n in the column index (dbwy)
      for(n = i; n < i+end; n++) {
        if(std::abs(m(j,n).imag()) > PRINT_SMALL)
          output << std::setw(15) << std::right << m(j,n).imag(); // n in the column index (dbwy)
        else
          output << std::setw(15) << std::right << std::abs(m(j,n).imag()); // n in the column index (dbwy)
      }
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  }

  template<typename Derived>
  void prettyPrintTCS(std::ostream & output, const Derived& m, std::string str){
  int list = 5;
  int i,j,k,n,end,endLT;
  output.precision(10);
  output.fill(' ');
  output.setf(std::ios::right,std::ios::scientific);
  output.setf(std::ios::fixed,std::ios::floatfield);
  output << std::endl << "\u03B1-\u03B1 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "\u03B2-\u03B2 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n+1); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "\u03B1-\u03B2 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n+1); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "\u03B2-\u03B1 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  }


  template<typename Derived>
  void prettyPrintTCSComplex(std::ostream & output, const Derived& m, std::string str){
  int list = 5;
  int i,j,k,n,end,endLT;
  output.precision(10);
  output.fill(' ');
  output.setf(std::ios::right,std::ios::scientific);
  output.setf(std::ios::fixed,std::ios::floatfield);
  output << std::endl << "Re(\u03B1-\u03B1 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n).real(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Im(\u03B1-\u03B1 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n).imag(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Re(\u03B2-\u03B2 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n+1).real(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Im(\u03B2-\u03B2 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n+1).imag(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Re(\u03B1-\u03B2 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n+1).real(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Im(\u03B1-\u03B2 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,2*n+1).imag(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Re(\u03B2-\u03B1 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n).real(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "Im(\u03B2-\u03B1 [" << str <<  "]): " << std::endl;
  output << bannerTop;

  for(i=0;i<(m.cols()/2);i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= (m.cols()/2)) end = (m.cols()/2) - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,2*n).imag(); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  }


  template<typename Derived>
  void prettyPrintTCSOD(std::ostream & output, const Derived& m, std::string str){
  int list = 5;
  int i,j,k,n,end,endLT;
  output.precision(10);
  output.fill(' ');
  output.setf(std::ios::right,std::ios::scientific);
  output.setf(std::ios::fixed,std::ios::floatfield);
  output << std::endl << "\u03B1 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<m.cols();i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= m.cols()) end = m.cols() - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j,n); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;
  output << std::endl << "\u03B2 [" << str <<  "]: " << std::endl;
  output << bannerTop;

  for(i=0;i<m.cols();i+=list) {
    output << std::endl;
    end = list;
    output << std::setw(5) << " ";
    if((i + list) >= m.cols()) end = m.cols() - i;
    for(k = i; k < i+end; k++) output << std::setw(15) << k+1;
    output << std::endl;
    for(j = 0;j < (m.rows()/2); j++) {
      output << std::setw(5) << std::left << j+1;
      for(n = i; n < i+end; n++) output << std::setw(15) << std::right << m(2*j+1,n); // n in the column index (dbwy)
      output << std::endl;
    };
  };
  output << bannerEnd << std::endl;

  }

  template<typename Derived>
  void eigSort(bool doL, Derived &E, Derived &VR, Derived &VL){
    for(auto i = 0  ; i < VR.rows()-1; i++)
    for(auto j = i+1; j < VR.rows()  ; j++) {
      if(E(i) > E(j)) {
        E(i).swap(E(j));
        VR.col(i).swap(VR.col(j));
        if(doL) VL.col(i).swap(VL.col(j));
      }
    }
  }

  template<typename Derived>
  void biOrth(Derived &L, Derived &R){
    for(auto i = 0; i < R.cols(); i++){
      double inner = std::abs(L.col(i).dot(R.col(i)));
      std::cout << inner << std::endl;
      L.col(i) = L.col(i) / std::sqrt(inner);
      R.col(i) = R.col(i) / std::sqrt(inner);
      for(auto j = i+1; j < R.cols(); j++){
        R.col(j) = R.col(j) - R.col(j).dot(L.col(i))*L.col(i);
      }
    }
  }
}
#endif
