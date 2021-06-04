#!/bin/tcsh
setenv CI_SEP -
setenv CI_BUILD_TYPE debug
setenv CI_BUILD_SUFFIX build
setenv CI_MACHINE_ARCH ppc
setenv CI_COMPILER_FAMILY xl
setenv CI_COMPILER_VER 16.1.1.6
setenv CI_COMPILER_NAME $CI_COMPILER_FAMILY$CI_SEP$CI_COMPILER_VER$CI_SEP
setenv CI_CUDA_PREFIX cuda
setenv CI_CUDA_VER 
setenv CI_CUDA_NAME 
setenv CI_KOKKOS_PREFIX kokkos
setenv CI_KOKKOS_VER 3.1.01
setenv CI_KOKKOS_BACKEND openmp
setenv CI_KOKKOS_NAME $CI_KOKKOS_PREFIX$CI_SEP$CI_KOKKOS_VER$CI_SEP$CI_KOKKOS_BACKEND$CI_SEP$CI_BUILD_TYPE
setenv CI_PATH_PREFIX /home/$USER/kt
setenv CI_INSTALL_DIR $CI_PATH_PREFIX/$CI_MACHINE_ARCH$CI_SEP$CI_COMPILER_NAME$CI_CUDA_NAME$CI_KOKKOS_NAME
setenv CI_BUILD_DIR $CI_INSTALL_DIR$CI_SEP$CI_BUILD_SUFFIX
rm -rf $CI_INSTALL_DIR
rm -rf $CI_BUILD_DIR
mkdir -p $CI_INSTALL_DIR
mkdir -p $CI_BUILD_DIR
module load cmake/3.19.2
module load gcc/7.4.0
module load ibm/xlc-16.1.1.6-xlf-16.1.1.6
setenv CXXFLAGS "-F/projects/opt/ppc64le/ibm/xlc-16.1.1.6/xlC/16.1.1/etc/xlc.cfg.rhel.7.7.gcc.7.4.0.cuda.10.1"
cd $CI_BUILD_DIR
cmake /home/$USER/$CI_KOKKOS_PREFIX/$CI_KOKKOS_PREFIX$CI_SEP$CI_KOKKOS_VER \
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON \
    -DCMAKE_INSTALL_PREFIX=$CI_INSTALL_DIR \
    -DKokkos_ENABLE_SERIAL=ON -DKokkos_ENABLE_OPENMP=ON \
    -DKokkos_ENABLE_TESTS=ON
setenv OMP_PROC_BIND spread
setenv OMP_PLACES threads
cmake --build $CI_BUILD_DIR --parallel
cmake --install $CI_BUILD_DIR
ctest
module purge
rm -rf $CI_BUILD_DIR
