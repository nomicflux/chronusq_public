%chk=4.chk
#p hf/sto-3g GFInput nosymm scf=incore 6d scf=tight iop(3/33=10,5/33=10) output=RawMatrixElement

d

0 1
c  0.0  0.1 0.0
c  1.0  0.0 0.15

file.out

C 0
S    3 1.00
 0.7161683735e+02  0.1543289673e+00
 0.1304509632e+02  0.5353281423e+00
 0.3530512160e+01  0.4446345422e+00
SP   3 1.00
 0.2941249355e+01 -0.9996722919e-01  0.1559162750e+00
 0.6834830964e+00  0.3995128261e+00  0.6076837186e+00
 0.2222899159e+00  0.7001154689e+00  0.3919573931e+00
D   3  1.00
       30.8534100         0.919990500E-01
       8.26498500         0.398502100
       2.49533200         0.691789700
****

