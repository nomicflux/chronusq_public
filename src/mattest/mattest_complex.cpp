#include "matrix.h"

void complex_test(int N,int M){
  // Allocate Matricies
  Matrix<dcomplex> *A = new Matrix<dcomplex>(N,N,"A","STD");
  Matrix<dcomplex> *B = new Matrix<dcomplex>(N,M,"B","STD");
  Matrix<dcomplex> *C = new Matrix<dcomplex>(N,1,"C","STD");
  Matrix<dcomplex> *D = new Matrix<dcomplex>(M,1,"D","STD");

  Matrix<dcomplex> *AB = new Matrix<dcomplex>(N,M,"AB = A*B","STD");
  Matrix<dcomplex> *AC = new Matrix<dcomplex>(N,1,"AC = A*C","STD");
  Matrix<dcomplex> *BD = new Matrix<dcomplex>(N,1,"BD = B*D","STD");

  Matrix<dcomplex> *A_Vec = new Matrix<dcomplex>(N,N,"A Eigenvector","STD");
  Matrix<dcomplex> *A_Eig = new Matrix<dcomplex>(N,N,"A Eigenvalues","STD");

  Matrix<dcomplex> *AT  = new Matrix<dcomplex>(N,N,"Back-transformed -> A","STD");
  Matrix<dcomplex> *AET = new Matrix<dcomplex>(N,N,"Back-transformed -> A_Eig","STD");

  Matrix<dcomplex> *SqrtA = new Matrix<dcomplex>(N,N,"[A]^2","STD");
  Matrix<dcomplex>  *ExpA = new Matrix<dcomplex>(N,N,"Exp[A]","STD");

  Matrix<dcomplex> *VcT = new Matrix<dcomplex>(N,N,"VcT");
  Matrix<dcomplex> *tmp = new Matrix<dcomplex>(N,N,"VTV");

  // Clear Contents
  A->setSymm('H');
  A->clearAll();
  B->clearAll();
  C->clearAll();
  D->clearAll();
  A_Eig->clearAll();
  A_Vec->clearAll();
  VcT->clearAll();
  tmp->clearAll();

  // Initialize Test Matricies
  for(int i = 0; i < N; i++)
  for(int j = 0; j < N; j++){
    if(i<j)(*A)(i,j) = dcomplex(i + j,i*j);
    if(i>j)(*A)(i,j) = dcomplex(i + j,-i*j);
  }
  A->scale(0.01);

  for(int i = 0; i < N; i++)
  for(int j = 0; j < M; j++){
    (*B)(i,j) = i * j;
  }

  
  for(int i = 0; i < N; i++){
    (*C)(i,0) = (dcomplex)i + (dcomplex)(1.0/(i+1));
  }

  for(int i = 0; i < M; i++){
    (*D)(i,0) = (dcomplex)i + (dcomplex)(1.0/(i*i+1));
  }

  // Perform Operations
  (*AB) = (*A)*(*B);
  (*AC) = (*A)*(*C);
  (*BD) = (*B)*(*D);

  cout << "Here before diag" << endl;
//A->setSymm('G');
  try{ A->diag();}
  catch(int msg){ cout << msg << endl;}
  cout << "Here after diag" << endl;
//try{B->diag();}
//catch(int msg) {CErr(msg);}; 
  
  cout << "Here" << endl;
  try{
  (*A_Vec) =     A->eigenvector();
  cout << "Here" << endl;
    A_Eig->setDag(A->eigenvalue_re());  
  } catch (int msg){ cout << msg << endl;};
  cout << "Here" << endl;
  try{ (*AT) = A_Eig->transNT(*A_Vec);}
  catch(int msg){ cout << msg << endl;}
  (*AET) = A->transTN(*A_Vec);
  cout << "Here" << endl;
  A->printAll();
  AT->printAll();
  A_Eig->printAll();
  AET->printAll();
/*

  (*SqrtA) = (*A)^2.0;
  (*ExpA) = exp(*A);
  SqrtA->printAll();
  ExpA->printAll();
  A_Vec->printAll();
*/
  (*VcT) = A_Vec;
  VcT->adjoint();
  (*tmp) = (*VcT)*(*A_Vec);
  tmp->printAll();
  
  delete A;
  delete B;
  delete C;
  delete A_Vec;
  delete A_Eig;
  delete SqrtA;
  delete ExpA;
}
