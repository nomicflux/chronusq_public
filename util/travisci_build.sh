mkdir build_gcc_libint_openmp
cp -r Test build_gcc_libint_openmp
cd build_gcc_libint_openmp
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_Fortran_COMPILER=gfortran -DCMAKE_CXX_FLAGS='-w -O3 -std=c++11 -I $(PWD)/../deps/eigen -I $(PWD)/../deps/BTAS' -DCMAKE_C_COMPILER=gcc -DUSE_LIBINT=ON -DUSE_OMP=ON ..
make VERBOSE=1 -j8

