// Copyright (c) 2019. Triad National Security, LLC. All rights reserved.
//
// This program was produced under U.S. Government contract 89233218CNA000001 for
// Los Alamos National Laboratory (LANL), which is operated by Triad National
// Security, LLC for the U.S. Department of Energy/National Nuclear Security
// Administration. All rights in the program are reserved by Triad National
// Security, LLC, and the U.S. Department of Energy/National Nuclear Security
// Administration. The Government is granted for itself and others acting on
// its behalf a nonexclusive, paid-up, irrevocable worldwide license in this
// material to reproduce, prepare derivative works, distribute copies to the
// public, perform publicly and display publicly, and to permit others to do so.
//
// This program is open source under the BSD-3 License.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the
//   names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <flcl-test-cxx.h>
#include <Kokkos_Core.hpp>
#include <flcl-cxx.hpp>
#include <iostream>
#include <iomanip>
#include <complex.h>

extern "C" {

  size_t c_test_ndarray_l_1d( flcl_ndarray_t *nd_array_l_1d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_1d = view_from_ndarray<bool*>(*nd_array_l_1d);

    for (size_t ii = 0; ii < array_l_1d.extent(0); ii++) {
      if ( array_l_1d(ii) ) c_sum++;
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_1d.extent(0); ii++) {
      array_l_1d(ii) = logical_post;
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_1d( flcl_ndarray_t *nd_array_i32_1d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_1d = view_from_ndarray<int32_t*>(*nd_array_i32_1d);
    
    for (size_t ii = 0; ii < array_i32_1d.extent(0); ii++) {
      c_sum = c_sum + array_i32_1d(ii);
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_1d.extent(0); ii++) {
      array_i32_1d(ii) = ii;
      c_sum = c_sum + array_i32_1d(ii);
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_1d( flcl_ndarray_t *nd_array_i64_1d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_1d = view_from_ndarray<int64_t*>(*nd_array_i64_1d);

    for (size_t ii = 0; ii < array_i64_1d.extent(0); ii++) {
      c_sum = c_sum + array_i64_1d(ii);
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED ndarray_i64_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);     
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_1d.extent(0); ii++) {
      array_i64_1d(ii) = ii;
      c_sum = c_sum + array_i64_1d(ii);
    }

    return c_sum;
  }

  float c_test_ndarray_r32_1d( flcl_ndarray_t *nd_array_r32_1d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_1d = view_from_ndarray<float*>(*nd_array_r32_1d);

    for (size_t ii = 0; ii < array_r32_1d.extent(0); ii++) {
      c_sum = c_sum + array_r32_1d(ii);
    }

    if ( std::abs(c_sum - *f_sum) > precision_single * c_sum) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_1d.extent(0); ii++) {
      array_r32_1d(ii) = ii;
      c_sum = c_sum + array_r32_1d(ii);
    }

    return c_sum;
  }

  double c_test_ndarray_r64_1d( flcl_ndarray_t *nd_array_r64_1d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_1d = view_from_ndarray<double*>(*nd_array_r64_1d);

    for (size_t ii = 0; ii < array_r64_1d.extent(0); ii++) {
      c_sum = c_sum + array_r64_1d(ii);
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_1d.extent(0); ii++) {
      array_r64_1d(ii) = ii;
      c_sum = c_sum + array_r64_1d(ii);
    }

    return c_sum;
  }

  float _Complex c_test_ndarray_c32_1d( flcl_ndarray_t *nd_array_c32_1d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_1d = view_from_ndarray<Kokkos::complex<float>*>(*nd_array_c32_1d);
    for (size_t ii = 0; ii < array_c32_1d.extent(0); ii++) {
      c_sum = c_sum + array_c32_1d(ii);
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_1d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_1d.extent(0); ii++) {
      array_c32_1d(ii) = Kokkos::complex<float>(1.0*(ii),-1.0*(ii));
      c_sum = c_sum + array_c32_1d(ii);
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;

  }

  double _Complex c_test_ndarray_c64_1d( flcl_ndarray_t *nd_array_c64_1d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_1d = view_from_ndarray<Kokkos::complex<double>*>(*nd_array_c64_1d);
    for (size_t ii = 0; ii < array_c64_1d.extent(0); ii++) {
      c_sum = c_sum + array_c64_1d(ii);
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_1d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_1d.extent(0); ii++) {
      array_c64_1d(ii) = Kokkos::complex<double>(1.0*(ii),-1.0*(ii));
      c_sum = c_sum + array_c64_1d(ii);
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;

  }

  size_t c_test_ndarray_l_2d( flcl_ndarray_t *nd_array_l_2d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_2d = view_from_ndarray<bool**>(*nd_array_l_2d);

    for (size_t ii = 0; ii < array_l_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_2d.extent(1); jj++) { 
        if ( array_l_2d(ii,jj) ) c_sum++;
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_2d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_2d.extent(1); jj++) {
        array_l_2d(ii,jj) = logical_post;
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_2d( flcl_ndarray_t *nd_array_i32_2d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_2d = view_from_ndarray<int32_t**>(*nd_array_i32_2d);

    for (size_t ii = 0; ii < array_i32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_2d.extent(1); jj++) {
        c_sum = c_sum + array_i32_2d(ii,jj);
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_2d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_2d.extent(1); jj++) {
        array_i32_2d(ii,jj) = ii+jj;
        c_sum = c_sum + array_i32_2d(ii,jj);
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_2d( flcl_ndarray_t *nd_array_i64_2d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_2d = view_from_ndarray<int64_t**>(*nd_array_i64_2d);

    for (size_t ii = 0; ii < array_i64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_2d.extent(1); jj++) {
        c_sum = c_sum + array_i64_2d(ii,jj);
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_2d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_2d.extent(1); jj++) {
        array_i64_2d(ii,jj) = ii+jj;
        c_sum = c_sum + array_i64_2d(ii,jj);
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_2d( flcl_ndarray_t *nd_array_r32_2d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_2d = view_from_ndarray<float**>(*nd_array_r32_2d);

    for (size_t ii = 0; ii < array_r32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_2d.extent(1); jj++) {
        c_sum = c_sum + array_r32_2d(ii,jj);
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_single * c_sum) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_2d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_2d.extent(1); jj++) {
        array_r32_2d(ii,jj) = ii+jj;
        c_sum = c_sum + array_r32_2d(ii,jj);
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_2d( flcl_ndarray_t *nd_array_r64_2d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_2d = view_from_ndarray<double**>(*nd_array_r64_2d);

    for (size_t ii = 0; ii < array_r64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_2d.extent(1); jj++) {
        c_sum = c_sum + array_r64_2d(ii,jj);
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_1d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_2d.extent(1); jj++) {
        array_r64_2d(ii,jj) = ii+jj;
        c_sum = c_sum + array_r64_2d(ii,jj);
      }
    }

    return c_sum;
  }

  float _Complex c_test_ndarray_c32_2d( flcl_ndarray_t *nd_array_c32_2d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_2d = view_from_ndarray<Kokkos::complex<float>**>(*nd_array_c32_2d);
    for (size_t ii = 0; ii < array_c32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_2d.extent(1); jj++) {
        c_sum = c_sum + array_c32_2d(ii,jj);
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_2d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_2d.extent(1); jj++) {
        array_c32_2d(ii,jj) = Kokkos::complex<float>(1.0*(ii+jj),-1.0*(ii+jj));
        c_sum = c_sum + array_c32_2d(ii,jj);
      }
    }

    // float _Complex c_sum_to_return;
    // c_sum_to_return = c_sum.real() + c_sum.imag()*I;
    // return c_sum_to_return;

    // float _Complex c_sum_to_return;
    // Kokkos::View<Kokkos::complex<float>*, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged> kvtr = 
    // Kokkos::View<Kokkos::complex<float>*, Kokkos::LayoutLeft, Kokkos::HostSpace, Kokkos::MemoryUnmanaged>(reinterpret_cast<Kokkos::complex<float> *>(&c_sum_to_return));
    // kvtr(0) = c_sum;
    // return c_sum_to_return;
    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_2d( flcl_ndarray_t *nd_array_c64_2d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_2d = view_from_ndarray<Kokkos::complex<double>**>(*nd_array_c64_2d);
    for (size_t ii = 0; ii < array_c64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_2d.extent(1); jj++) {
        c_sum = c_sum + array_c64_2d(ii,jj);
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_2d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_2d.extent(1); jj++) {
        array_c64_2d(ii,jj) = Kokkos::complex<double>(1.0*(ii+jj),-1.0*(ii+jj));
        c_sum = c_sum + array_c64_2d(ii,jj);
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  size_t c_test_ndarray_l_3d( flcl_ndarray_t *nd_array_l_3d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_3d = view_from_ndarray<bool***>(*nd_array_l_3d);

    for (size_t ii = 0; ii < array_l_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_3d.extent(2); kk++) {
          if ( array_l_3d(ii,jj,kk) ) c_sum++;
        }
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_3d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_3d.extent(2); kk++) {
          array_l_3d(ii,jj,kk) = logical_post;
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_3d( flcl_ndarray_t *nd_array_i32_3d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_3d = view_from_ndarray<int32_t***>(*nd_array_i32_3d);

    for (size_t ii = 0; ii < array_i32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_3d.extent(2); kk++) {
          c_sum = c_sum + array_i32_3d(ii,jj,kk);
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_3d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_3d.extent(2); kk++) {
          array_i32_3d(ii,jj,kk) = ii+jj+kk;
          c_sum = c_sum + array_i32_3d(ii,jj,kk);
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_3d( flcl_ndarray_t *nd_array_i64_3d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_3d = view_from_ndarray<int64_t***>(*nd_array_i64_3d);

    for (size_t ii = 0; ii < array_i64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_3d.extent(2); kk++) {
          c_sum = c_sum + array_i64_3d(ii,jj,kk);
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_3d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_3d.extent(2); kk++) {
          array_i64_3d(ii,jj,kk) = ii+jj+kk;
          c_sum = c_sum + array_i64_3d(ii,jj,kk);
        }
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_3d( flcl_ndarray_t *nd_array_r32_3d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_3d = view_from_ndarray<float***>(*nd_array_r32_3d);

    for (size_t ii = 0; ii < array_r32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_3d.extent(2); kk++) {
          c_sum = c_sum + array_r32_3d(ii,jj,kk);
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_single * c_sum) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_3d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_3d.extent(2); kk++) {
          array_r32_3d(ii,jj,kk) = ii+jj+kk;
          c_sum = c_sum + array_r32_3d(ii,jj,kk);
        }
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_3d( flcl_ndarray_t *nd_array_r64_3d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_3d = view_from_ndarray<double***>(*nd_array_r64_3d);

    for (size_t ii = 0; ii < array_r64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_3d.extent(2); kk++) {
          c_sum = c_sum + array_r64_3d(ii,jj,kk);
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_3d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_3d.extent(2); kk++) {
          array_r64_3d(ii,jj,kk) = ii+jj+kk;
          c_sum = c_sum + array_r64_3d(ii,jj,kk);
        }
      }
    }

    return c_sum;

  }

  float _Complex c_test_ndarray_c32_3d( flcl_ndarray_t *nd_array_c32_3d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_3d = view_from_ndarray<Kokkos::complex<float>***>(*nd_array_c32_3d);
    for (size_t ii = 0; ii < array_c32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_3d.extent(2); kk++) {
          c_sum = c_sum + array_c32_3d(ii,jj,kk);
        }
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_3d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_3d.extent(2); kk++) {
          array_c32_3d(ii,jj,kk) = Kokkos::complex<float>(1.0*(ii+jj+kk),-1.0*(ii+jj+kk));
          c_sum = c_sum + array_c32_3d(ii,jj,kk);
        }
      }
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_3d( flcl_ndarray_t *nd_array_c64_3d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_3d = view_from_ndarray<Kokkos::complex<double>***>(*nd_array_c64_3d);
    for (size_t ii = 0; ii < array_c64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_3d.extent(2); kk++) {
          c_sum = c_sum + array_c64_3d(ii,jj,kk);
          // std::cout << "c ii "<< ii << " jj " << " kk " << kk << " c_sum " << c_sum << std::endl;
        }
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_3d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_3d.extent(2); kk++) {
          array_c64_3d(ii,jj,kk) = Kokkos::complex<double>(1.0*(ii+jj+kk),-1.0*(ii+jj+kk));
          // c_sum = c_sum + array_c64_3d(ii,jj,kk);
          c_sum = c_sum + array_c64_3d(ii,jj,kk);
          // std::cout << "c ii "<< ii << " jj " << " kk " << kk << " c_sum " << c_sum << std::endl;
        }
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  size_t c_test_ndarray_l_4d( flcl_ndarray_t *nd_array_l_4d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_4d = view_from_ndarray<bool****>(*nd_array_l_4d);

    for (size_t ii = 0; ii < array_l_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_4d.extent(3); ll++) {
            if ( array_l_4d(ii,jj,kk,ll) ) c_sum++;
          }
        }
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_4d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_4d.extent(3); ll++) {
            array_l_4d(ii,jj,kk,ll) = logical_post;
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_4d( flcl_ndarray_t *nd_array_i32_4d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_4d = view_from_ndarray<int32_t****>(*nd_array_i32_4d);

    for (size_t ii = 0; ii < array_i32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_4d.extent(3); ll++) {
            c_sum = c_sum + array_i32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_4d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_4d.extent(3); ll++) {
            array_i32_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            c_sum = c_sum + array_i32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_4d( flcl_ndarray_t *nd_array_i64_4d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_4d = view_from_ndarray<int64_t****>(*nd_array_i64_4d);

    for (size_t ii = 0; ii < array_i64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_4d.extent(3); ll++) {
            c_sum = c_sum + array_i64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_4d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_4d.extent(3); ll++) {
            array_i64_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            c_sum = c_sum + array_i64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_4d( flcl_ndarray_t *nd_array_r32_4d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_4d = view_from_ndarray<float****>(*nd_array_r32_4d);

    for (size_t ii = 0; ii < array_r32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_4d.extent(3); ll++) {
            c_sum = c_sum + array_r32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_single * c_sum) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_4d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_4d.extent(3); ll++) {
            array_r32_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            c_sum = c_sum + array_r32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_4d( flcl_ndarray_t *nd_array_r64_4d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_4d = view_from_ndarray<double****>(*nd_array_r64_4d);

    for (size_t ii = 0; ii < array_r64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_4d.extent(3); ll++) {
            c_sum = c_sum + array_r64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_4d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_4d.extent(3); ll++) {
            array_r64_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            c_sum = c_sum + array_r64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    return c_sum;

  }

  float _Complex c_test_ndarray_c32_4d( flcl_ndarray_t *nd_array_c32_4d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_4d = view_from_ndarray<Kokkos::complex<float>****>(*nd_array_c32_4d);
    for (size_t ii = 0; ii < array_c32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_4d.extent(3); ll++) {
            c_sum = c_sum + array_c32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_4d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_4d.extent(3); ll++) {
            array_c32_4d(ii,jj,kk,ll) = Kokkos::complex<float>(1.0*(ii+jj+kk+ll),-1.0*(ii+jj+kk+ll));
            c_sum = c_sum + array_c32_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_4d( flcl_ndarray_t *nd_array_c64_4d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_4d = view_from_ndarray<Kokkos::complex<double>****>(*nd_array_c64_4d);
    for (size_t ii = 0; ii < array_c64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_4d.extent(3); ll++) {
            c_sum = c_sum + array_c64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_4d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_4d.extent(3); ll++) {
            array_c64_4d(ii,jj,kk,ll) = Kokkos::complex<double>(1.0*(ii+jj+kk+ll),-1.0*(ii+jj+kk+ll));
            c_sum = c_sum + array_c64_4d(ii,jj,kk,ll);
          }
        }
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  size_t c_test_ndarray_l_5d( flcl_ndarray_t *nd_array_l_5d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_5d = view_from_ndarray<bool*****>(*nd_array_l_5d);

    for (size_t ii = 0; ii < array_l_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_5d.extent(4); mm++) {
              if ( array_l_5d(ii,jj,kk,ll,mm) ) c_sum++;
            }
          }
        }
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_5d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_5d.extent(4); mm++) {
              array_l_5d(ii,jj,kk,ll,mm) = logical_post;
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_5d( flcl_ndarray_t *nd_array_i32_5d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_5d = view_from_ndarray<int32_t*****>(*nd_array_i32_5d);

    for (size_t ii = 0; ii < array_i32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_5d.extent(4); mm++) {
              c_sum = c_sum + array_i32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_5d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_5d.extent(4); mm++) {
              array_i32_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              c_sum = c_sum + array_i32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_5d( flcl_ndarray_t *nd_array_i64_5d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_5d = view_from_ndarray<int64_t*****>(*nd_array_i64_5d);

    for (size_t ii = 0; ii < array_i64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_5d.extent(4); mm++) {
              c_sum = c_sum + array_i64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_5d" << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_5d.extent(4); mm++) {
              array_i64_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              c_sum = c_sum + array_i64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_5d( flcl_ndarray_t *nd_array_r32_5d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_5d = view_from_ndarray<float*****>(*nd_array_r32_5d);

    for (size_t ii = 0; ii < array_r32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_5d.extent(4); mm++) {
              c_sum = c_sum + array_r32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > (precision_single * c_sum) ) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_5d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "std::abs(c_sum - *f_sum) = " << std::abs(c_sum - *f_sum) << std::endl;
      std::cout << "(precision_single * c_sum) = " << (precision_single * c_sum) << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_5d.extent(4); mm++) {
              array_r32_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              c_sum = c_sum + array_r32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_5d( flcl_ndarray_t *nd_array_r64_5d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_5d = view_from_ndarray<double*****>(*nd_array_r64_5d);

    for (size_t ii = 0; ii < array_r64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_5d.extent(4); mm++) {
              c_sum = c_sum + array_r64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_5d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_5d.extent(4); mm++) {
              array_r64_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              c_sum = c_sum + array_r64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    return c_sum;

  }

  float _Complex c_test_ndarray_c32_5d( flcl_ndarray_t *nd_array_c32_5d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_5d = view_from_ndarray<Kokkos::complex<float>*****>(*nd_array_c32_5d);
    for (size_t ii = 0; ii < array_c32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_5d.extent(4); mm++) {
              c_sum = c_sum + array_c32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_5d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_5d.extent(4); mm++) {
              array_c32_5d(ii,jj,kk,ll,mm) = Kokkos::complex<float>(1.0*(ii+jj+kk+ll+mm),-1.0*(ii+jj+kk+ll+mm));
              c_sum = c_sum + array_c32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_5d( flcl_ndarray_t *nd_array_c64_5d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_5d = view_from_ndarray<Kokkos::complex<double>*****>(*nd_array_c64_5d);
    for (size_t ii = 0; ii < array_c64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_5d.extent(4); mm++) {
              c_sum = c_sum + array_c64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_5d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_5d.extent(4); mm++) {
              array_c64_5d(ii,jj,kk,ll,mm) = Kokkos::complex<double>(1.0*(ii+jj+kk+ll+mm),-1.0*(ii+jj+kk+ll+mm));
              c_sum = c_sum + array_c64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  size_t c_test_ndarray_l_6d( flcl_ndarray_t *nd_array_l_6d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_6d = view_from_ndarray<bool******>(*nd_array_l_6d);

    for (size_t ii = 0; ii < array_l_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_6d.extent(5); nn++) {
                if ( array_l_6d(ii,jj,kk,ll,mm,nn) ) c_sum++;
              }
            }
          }
        }
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_6d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_6d.extent(5); nn++) {
                array_l_6d(ii,jj,kk,ll,mm,nn) = logical_post;
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_6d( flcl_ndarray_t *nd_array_i32_6d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_6d = view_from_ndarray<int32_t******>(*nd_array_i32_6d);

    for (size_t ii = 0; ii < array_i32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_6d.extent(5); nn++) {
                c_sum = c_sum + array_i32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_6d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_6d.extent(5); nn++) {
                array_i32_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                c_sum = c_sum + array_i32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_6d( flcl_ndarray_t *nd_array_i64_6d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_6d = view_from_ndarray<int64_t******>(*nd_array_i64_6d);

    for (size_t ii = 0; ii < array_i64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_6d.extent(5); nn++) {
                c_sum = c_sum + array_i64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_6d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_6d.extent(5); nn++) {
                array_i64_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                c_sum = c_sum + array_i64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_6d( flcl_ndarray_t *nd_array_r32_6d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_6d = view_from_ndarray<float******>(*nd_array_r32_6d);

    for (size_t ii = 0; ii < array_r32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_6d.extent(5); nn++) {
                c_sum = c_sum + array_r32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > (precision_single * c_sum) ) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_6d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "std::abs(c_sum - *f_sum) = " << std::abs(c_sum - *f_sum) << std::endl;
      std::cout << "(precision_single * c_sum) = " << (precision_single * c_sum) << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_6d.extent(5); nn++) {
                array_r32_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                c_sum = c_sum + array_r32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_6d( flcl_ndarray_t *nd_array_r64_6d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_6d = view_from_ndarray<double******>(*nd_array_r64_6d);

    for (size_t ii = 0; ii < array_r64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_6d.extent(5); nn++) {
                c_sum = c_sum + array_r64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_6d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_6d.extent(5); nn++) {
                array_r64_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                c_sum = c_sum + array_r64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    return c_sum;

  }

  float _Complex c_test_ndarray_c32_6d( flcl_ndarray_t *nd_array_c32_6d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_6d = view_from_ndarray<Kokkos::complex<float>******>(*nd_array_c32_6d);
    for (size_t ii = 0; ii < array_c32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c32_6d.extent(5); nn++) {
                c_sum = c_sum + array_c32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_5d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c32_6d.extent(5); nn++) {
                array_c32_6d(ii,jj,kk,ll,mm,nn) = Kokkos::complex<float>(1.0*(ii+jj+kk+ll+mm+nn),-1.0*(ii+jj+kk+ll+mm+nn));
                c_sum = c_sum + array_c32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_6d( flcl_ndarray_t *nd_array_c64_6d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_6d = view_from_ndarray<Kokkos::complex<double>******>(*nd_array_c64_6d);
    for (size_t ii = 0; ii < array_c64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c64_6d.extent(5); nn++) {
                c_sum = c_sum + array_c64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_6d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c64_6d.extent(5); nn++) {
                array_c64_6d(ii,jj,kk,ll,mm,nn) = Kokkos::complex<double>(1.0*(ii+jj+kk+ll+mm+nn),-1.0*(ii+jj+kk+ll+mm+nn));
                c_sum = c_sum + array_c64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  size_t c_test_ndarray_l_7d( flcl_ndarray_t *nd_array_l_7d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_l_7d = view_from_ndarray<bool*******>(*nd_array_l_7d);

    for (size_t ii = 0; ii < array_l_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_l_7d.extent(6); oo++) {
                  if ( array_l_7d(ii,jj,kk,ll,mm,nn,oo) ) c_sum++;
                }
              }
            }
          }
        }
      }
    }

    if (c_sum != *f_sum) {
      std::cout << "FAILED C ndarray_l_7d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    for (size_t ii = 0; ii < array_l_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_l_7d.extent(6); oo++) {
                  array_l_7d(ii,jj,kk,ll,mm,nn,oo) = logical_post;
                }
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i32_7d( flcl_ndarray_t *nd_array_i32_7d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i32_7d = view_from_ndarray<int32_t*******>(*nd_array_i32_7d);

    for (size_t ii = 0; ii < array_i32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i32_7d.extent(6); oo++) {
                  c_sum = c_sum + array_i32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i32_7d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i32_7d.extent(6); oo++) {
                  array_i32_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  c_sum = c_sum + array_i32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  size_t c_test_ndarray_i64_7d( flcl_ndarray_t *nd_array_i64_7d, size_t *f_sum ) {
    using flcl::view_from_ndarray;

    size_t c_sum = 0;
    auto array_i64_7d = view_from_ndarray<int64_t*******>(*nd_array_i64_7d);

    for (size_t ii = 0; ii < array_i64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i64_7d.extent(6); oo++) {
                  c_sum = c_sum + array_i64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    if ( c_sum != *f_sum ) {
      std::cout << "FAILED C ndarray_i64_7d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_i64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i64_7d.extent(6); oo++) {
                  array_i64_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  c_sum = c_sum + array_i64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  float c_test_ndarray_r32_7d( flcl_ndarray_t *nd_array_r32_7d, float *f_sum ) {
    using flcl::view_from_ndarray;

    float c_sum = 0;
    auto array_r32_7d = view_from_ndarray<float*******>(*nd_array_r32_7d);

    for (size_t ii = 0; ii < array_r32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r32_7d.extent(6); oo++) {
                  c_sum = c_sum + array_r32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_single * c_sum) {
      std::cout << std::setprecision(8) << std::fixed;
      std::cout << "FAILED C ndarray_r32_7d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r32_7d.extent(6); oo++) {
                  array_r32_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  c_sum = c_sum + array_r32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    return c_sum;
  }

  double c_test_ndarray_r64_7d( flcl_ndarray_t *nd_array_r64_7d, double *f_sum ) {
    using flcl::view_from_ndarray;

    double c_sum = 0;
    auto array_r64_7d = view_from_ndarray<double*******>(*nd_array_r64_7d);

    for (size_t ii = 0; ii < array_r64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r64_7d.extent(6); oo++) {
                  c_sum = c_sum + array_r64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    if ( std::abs(c_sum - *f_sum) > precision_double * c_sum) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_r64_7d" << std::endl;
      std::cout << "c_sum = " << c_sum << std::endl;
      std::cout << "f_sum = " << *f_sum << std::endl;
      std::cout << "c_sum - *f_sum = " << c_sum - *f_sum << std::endl;
      exit(EXIT_FAILURE);    
    }

    c_sum = 0;
    for (size_t ii = 0; ii < array_r64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r64_7d.extent(6); oo++) {
                  array_r64_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  c_sum = c_sum + array_r64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    
    return c_sum;

  }

  float _Complex c_test_ndarray_c32_7d( flcl_ndarray_t *nd_array_c32_7d, float _Complex *f_sum ) {
    using flcl::view_from_ndarray;
    
    Kokkos::complex<float> c_sum(0.0,0.0);

    auto array_c32_7d = view_from_ndarray<Kokkos::complex<float>*******>(*nd_array_c32_7d);
    for (size_t ii = 0; ii < array_c32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_c32_7d.extent(6); oo++) {
                  c_sum = c_sum + array_c32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

     if ( (std::abs(c_sum.real() - crealf(*f_sum)) > precision_single * c_sum.real()) || (std::abs(c_sum.imag() - cimagf(*f_sum)) < precision_single * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c32_7d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "crealf(*f_sum) = " << crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimagf(*f_sum) = " << cimagf(*f_sum) << std::endl;
      std::cout << "c_sum.real() - crealf(*f_sum) = " << c_sum.real() - crealf(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimagf(*f_sum) = " << c_sum.imag() - cimagf(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - crealf(*f_sum)) / c_sum.real() = " << (c_sum.real() - crealf(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimagf(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);
    }

    c_sum = Kokkos::complex<float>(0.0,0.0);
    for (size_t ii = 0; ii < array_c32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_c32_7d.extent(6); oo++) {
                  array_c32_7d(ii,jj,kk,ll,mm,nn,oo) = Kokkos::complex<float>(1.0*(ii+jj+kk+ll+mm+nn+oo),-1.0*(ii+jj+kk+ll+mm+nn+oo));
                  c_sum = c_sum + array_c32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    float _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<float>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  double _Complex c_test_ndarray_c64_7d( flcl_ndarray_t *nd_array_c64_7d, double _Complex *f_sum ) {
    using flcl::view_from_ndarray;

    Kokkos::complex<double> c_sum(0.0,0.0);

    auto array_c64_7d = view_from_ndarray<Kokkos::complex<double>*******>(*nd_array_c64_7d);
    for (size_t ii = 0; ii < array_c64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_c64_7d.extent(6); oo++) {
                  c_sum = c_sum + array_c64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    if ( (std::abs(c_sum.real() - creal(*f_sum)) > precision_double * c_sum.real()) || (std::abs(c_sum.imag() - cimag(*f_sum)) < precision_double * c_sum.imag()) ) {
      std::cout << std::setprecision(15) << std::fixed;
      std::cout << "FAILED C ndarray_c64_7d" << std::endl;
      std::cout << "c_sum.real() = " << c_sum.real() << std::endl;
      std::cout << "creal(*f_sum) = " << creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() = " << c_sum.imag() << std::endl;
      std::cout << "cimag(*f_sum) = " << cimag(*f_sum) << std::endl;
      std::cout << "c_sum.real() - creal(*f_sum) = " << c_sum.real() - creal(*f_sum) << std::endl;
      std::cout << "c_sum.imag() - cimag(*f_sum) = " << c_sum.imag() - cimag(*f_sum) << std::endl;
      std::cout << "(c_sum.real() - creal(*f_sum)) / c_sum.real() = " << (c_sum.real() - creal(*f_sum)) / c_sum.real() << std::endl;
      std::cout << "(c_sum.imag() - cimag(*f_sum)) / c_sum.imag() = " << (c_sum.imag() - cimag(*f_sum)) / c_sum.imag() << std::endl;
      exit(EXIT_FAILURE);    
    }
    
    c_sum = Kokkos::complex<double>(0.0,0.0);
    for (size_t ii = 0; ii < array_c64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_c64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_c64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_c64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_c64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_c64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_c64_7d.extent(6); oo++) {
                  array_c64_7d(ii,jj,kk,ll,mm,nn,oo) = Kokkos::complex<double>(1.0*(ii+jj+kk+ll+mm+nn+oo),-1.0*(ii+jj+kk+ll+mm+nn+oo));
                  c_sum = c_sum + array_c64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }

    double _Complex c_sum_to_return;
    *reinterpret_cast<Kokkos::complex<double>*>(&c_sum_to_return) = c_sum;
    return c_sum_to_return;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_1d( flcl::view_l_1d_t **v_array_l_1d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_1d = **v_array_l_1d;
    for (size_t ii = 0; ii < array_l_1d.extent(0); ii++) {
      if ( array_l_1d(ii) ) (*c_sum)++;
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_1d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_1d.extent(0); ii++) {
      array_l_1d(ii) = logical_post;
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_1d( flcl::view_i32_1d_t **v_array_i32_1d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_1d = **v_array_i32_1d;
    for (size_t ii = 0; ii < array_i32_1d.extent(0); ii++) {
      *c_sum += array_i32_1d(ii);
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_1d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_1d.extent(0); ii++) {
      array_i32_1d(ii) = ii;
      *c_sum += array_i32_1d(ii);
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_1d( flcl::view_i64_1d_t **v_array_i64_1d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_1d = **v_array_i64_1d;
    for (size_t ii = 0; ii < array_i64_1d.extent(0); ii++) {
      *c_sum += array_i64_1d(ii);
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED ndarray_i64_1d" << std::endl;
      return FLCL_TEST_FAIL;  
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_1d.extent(0); ii++) {
      array_i64_1d(ii) = ii;
      *c_sum += array_i64_1d(ii);
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_1d( flcl::view_r32_1d_t **v_array_r32_1d, float *f_sum, float *c_sum ) {
    *c_sum = 0;
    auto array_r32_1d = **v_array_r32_1d;
    for (size_t ii = 0; ii < array_r32_1d.extent(0); ii++) {
      *c_sum += array_r32_1d(ii);
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C ndarray_r32_1d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_1d.extent(0); ii++) {
      array_r32_1d(ii) = ii;
      *c_sum += array_r32_1d(ii);
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_1d( flcl::view_r64_1d_t **v_array_r64_1d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_1d = **v_array_r64_1d;
    for (size_t ii = 0; ii < array_r64_1d.extent(0); ii++) {
      *c_sum += array_r64_1d(ii);
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C ndarray_r64_1d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_1d.extent(0); ii++) {
      array_r64_1d(ii) = ii;
      *c_sum += array_r64_1d(ii);
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_2d( flcl::view_l_2d_t **v_array_l_2d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_2d = **v_array_l_2d;
    for (size_t ii = 0; ii < array_l_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_2d.extent(1); jj++) { 
        if ( array_l_2d(ii,jj) ) (*c_sum)++;
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_2d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_2d.extent(1); jj++) {
        array_l_2d(ii,jj) = logical_post;
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_2d( flcl::view_i32_2d_t **v_array_i32_2d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_2d = **v_array_i32_2d;
    for (size_t ii = 0; ii < array_i32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_2d.extent(1); jj++) {
        *c_sum += array_i32_2d(ii,jj);
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_2d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_2d.extent(1); jj++) {
        array_i32_2d(ii,jj) = ii+jj;
        *c_sum += array_i32_2d(ii,jj);
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_2d( flcl::view_i64_2d_t **v_array_i64_2d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_2d = **v_array_i64_2d;
    for (size_t ii = 0; ii < array_i64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_2d.extent(1); jj++) {
        *c_sum += array_i64_2d(ii,jj);
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_2d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_2d.extent(1); jj++) {
        array_i64_2d(ii,jj) = ii+jj;
        *c_sum += array_i64_2d(ii,jj);
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_2d( flcl::view_r32_2d_t **v_array_r32_2d, float *f_sum, float *c_sum ) {
    *c_sum = 0;
    auto array_r32_2d = **v_array_r32_2d;
    for (size_t ii = 0; ii < array_r32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_2d.extent(1); jj++) {
        *c_sum += array_r32_2d(ii,jj);
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_2d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_2d.extent(1); jj++) {
        array_r32_2d(ii,jj) = ii+jj;
        *c_sum += array_r32_2d(ii,jj);
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_2d( flcl::view_r64_2d_t **v_array_r64_2d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_2d = **v_array_r64_2d;
    for (size_t ii = 0; ii < array_r64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_2d.extent(1); jj++) {
        *c_sum += array_r64_2d(ii,jj);
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_2d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_2d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_2d.extent(1); jj++) {
        array_r64_2d(ii,jj) = ii+jj;
        *c_sum += array_r64_2d(ii,jj);
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_3d( flcl::view_l_3d_t **v_array_l_3d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_3d = **v_array_l_3d;
    for (size_t ii = 0; ii < array_l_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_3d.extent(2); kk++) {
          if ( array_l_3d(ii,jj,kk) ) (*c_sum)++;
        }
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_3d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_3d.extent(2); kk++) {
          array_l_3d(ii,jj,kk) = logical_post;
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_3d( flcl::view_i32_3d_t **v_array_i32_3d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_3d = **v_array_i32_3d;
    for (size_t ii = 0; ii < array_i32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_3d.extent(2); kk++) {
          *c_sum += array_i32_3d(ii,jj,kk);
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_3d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_3d.extent(2); kk++) {
          array_i32_3d(ii,jj,kk) = ii+jj+kk;
          *c_sum += array_i32_3d(ii,jj,kk);
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_3d( flcl::view_i64_3d_t **v_array_i64_3d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_3d = **v_array_i64_3d;
    for (size_t ii = 0; ii < array_i64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_3d.extent(2); kk++) {
          *c_sum += array_i64_3d(ii,jj,kk);
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_3d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_3d.extent(2); kk++) {
          array_i64_3d(ii,jj,kk) = ii+jj+kk;
          *c_sum += array_i64_3d(ii,jj,kk);
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_3d( flcl::view_r32_3d_t **v_array_r32_3d, float *f_sum, float *c_sum ) {
    *c_sum = 0;
    auto array_r32_3d = **v_array_r32_3d;
    for (size_t ii = 0; ii < array_r32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_3d.extent(2); kk++) {
          *c_sum += array_r32_3d(ii,jj,kk);
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_3d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_3d.extent(2); kk++) {
          array_r32_3d(ii,jj,kk) = ii+jj+kk;
          *c_sum += array_r32_3d(ii,jj,kk);
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_3d( flcl::view_r64_3d_t **v_array_r64_3d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_3d = **v_array_r64_3d;
    for (size_t ii = 0; ii < array_r64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_3d.extent(2); kk++) {
          *c_sum += array_r64_3d(ii,jj,kk);
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_3d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_3d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_3d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_3d.extent(2); kk++) {
          array_r64_3d(ii,jj,kk) = ii+jj+kk;
          *c_sum += array_r64_3d(ii,jj,kk);
        }
      }
    }
    return FLCL_TEST_PASS;

  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_4d( flcl::view_l_4d_t **v_array_l_4d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_4d = **v_array_l_4d;
    for (size_t ii = 0; ii < array_l_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_4d.extent(3); ll++) {
            if ( array_l_4d(ii,jj,kk,ll) ) (*c_sum)++;
          }
        }
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_4d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_4d.extent(3); ll++) {
            array_l_4d(ii,jj,kk,ll) = logical_post;
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_4d( flcl::view_i32_4d_t **v_array_i32_4d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_4d = **v_array_i32_4d;
    for (size_t ii = 0; ii < array_i32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_4d.extent(3); ll++) {
            *c_sum += array_i32_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_4d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_4d.extent(3); ll++) {
            array_i32_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            *c_sum += array_i32_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_4d( flcl::view_i64_4d_t **v_array_i64_4d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_4d = **v_array_i64_4d;
    for (size_t ii = 0; ii < array_i64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_4d.extent(3); ll++) {
            *c_sum += array_i64_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_4d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_4d.extent(3); ll++) {
            array_i64_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            *c_sum += array_i64_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_4d( flcl::view_r32_4d_t **v_array_r32_4d, float *f_sum, float *c_sum ) {
    *c_sum = 0;
    auto array_r32_4d = **v_array_r32_4d;
    for (size_t ii = 0; ii < array_r32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_4d.extent(3); ll++) {
            *c_sum += array_r32_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_4d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_4d.extent(3); ll++) {
            array_r32_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            *c_sum += array_r32_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_4d( flcl::view_r64_4d_t **v_array_r64_4d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_4d = **v_array_r64_4d;
    for (size_t ii = 0; ii < array_r64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_4d.extent(3); ll++) {
            *c_sum += array_r64_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_4d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_4d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_4d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_4d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_4d.extent(3); ll++) {
            array_r64_4d(ii,jj,kk,ll) = ii+jj+kk+ll;
            *c_sum += array_r64_4d(ii,jj,kk,ll);
          }
        }
      }
    }
    return FLCL_TEST_PASS;

  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_5d( flcl::view_l_5d_t **v_array_l_5d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_5d = **v_array_l_5d;
    for (size_t ii = 0; ii < array_l_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_5d.extent(4); mm++) {
              if ( array_l_5d(ii,jj,kk,ll,mm) ) (*c_sum)++;
            }
          }
        }
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_5d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_5d.extent(4); mm++) {
              array_l_5d(ii,jj,kk,ll,mm) = logical_post;
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_5d( flcl::view_i32_5d_t **v_array_i32_5d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_5d = **v_array_i32_5d;
    for (size_t ii = 0; ii < array_i32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_5d.extent(4); mm++) {
              *c_sum += array_i32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_5d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_5d.extent(4); mm++) {
              array_i32_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              *c_sum += array_i32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_5d( flcl::view_i64_5d_t **v_array_i64_5d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_5d = **v_array_i64_5d;
    for (size_t ii = 0; ii < array_i64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_5d.extent(4); mm++) {
            *c_sum += array_i64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_5d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_5d.extent(4); mm++) {
              array_i64_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              *c_sum += array_i64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_5d( flcl::view_r32_5d_t **v_array_r32_5d, float *f_sum, float *c_sum ){
    *c_sum = 0;
    auto array_r32_5d = **v_array_r32_5d;
    for (size_t ii = 0; ii < array_r32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_5d.extent(4); mm++) {
              *c_sum += array_r32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_5d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_5d.extent(4); mm++) {
              array_r32_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              *c_sum += array_r32_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_5d( flcl::view_r64_5d_t **v_array_r64_5d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_5d = **v_array_r64_5d;
    for (size_t ii = 0; ii < array_r64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_5d.extent(4); mm++) {
              *c_sum += array_r64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_5d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_5d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_5d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_5d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_5d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_5d.extent(4); mm++) {
              array_r64_5d(ii,jj,kk,ll,mm) = ii+jj+kk+ll+mm;
              *c_sum += array_r64_5d(ii,jj,kk,ll,mm);
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;

  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_6d( flcl::view_l_6d_t **v_array_l_6d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_6d = **v_array_l_6d;
    for (size_t ii = 0; ii < array_l_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_6d.extent(5); nn++) {
                if ( array_l_6d(ii,jj,kk,ll,mm,nn) ) (*c_sum)++;
              }
            }
          }
        }
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_6d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_6d.extent(5); nn++) {
                array_l_6d(ii,jj,kk,ll,mm,nn) = logical_post;
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_6d( flcl::view_i32_6d_t **v_array_i32_6d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_6d = **v_array_i32_6d;
    for (size_t ii = 0; ii < array_i32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_6d.extent(5); nn++) {
                *c_sum += array_i32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_6d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_6d.extent(5); nn++) {
                array_i32_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                *c_sum += array_i32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_6d( flcl::view_i64_6d_t **v_array_i64_6d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_6d = **v_array_i64_6d;
    for (size_t ii = 0; ii < array_i64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_6d.extent(5); nn++) {
                *c_sum += array_i64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_6d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_6d.extent(5); nn++) {
                array_i64_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                *c_sum += array_i64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_6d( flcl::view_r32_6d_t **v_array_r32_6d, float *f_sum, float *c_sum ){
    *c_sum = 0;
    auto array_r32_6d = **v_array_r32_6d;
    for (size_t ii = 0; ii < array_r32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_6d.extent(5); nn++) {
                *c_sum += array_r32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_6d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_6d.extent(5); nn++) {
                array_r32_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                *c_sum += array_r32_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_6d( flcl::view_r64_6d_t **v_array_r64_6d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_6d = **v_array_r64_6d;
    for (size_t ii = 0; ii < array_r64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_6d.extent(5); nn++) {
                *c_sum += array_r64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_6d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_6d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_6d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_6d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_6d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_6d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_6d.extent(5); nn++) {
                array_r64_6d(ii,jj,kk,ll,mm,nn) = ii+jj+kk+ll+mm+nn;
                *c_sum += array_r64_6d(ii,jj,kk,ll,mm,nn);
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;

  }

  flcl_test_error_t c_test_kokkos_allocate_view_l_7d( flcl::view_l_7d_t **v_array_l_7d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_l_7d = **v_array_l_7d;
    for (size_t ii = 0; ii < array_l_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_l_7d.extent(6); oo++) {
                  if ( array_l_7d(ii,jj,kk,ll,mm,nn,oo) ) (*c_sum)++;
                }
              }
            }
          }
        }
      }
    }
    if (*c_sum != *f_sum) {
      std::cout << "FAILED C kokkos_allocate_view_l_7d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    for (size_t ii = 0; ii < array_l_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_l_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_l_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_l_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_l_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_l_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_l_7d.extent(6); oo++) {
                  array_l_7d(ii,jj,kk,ll,mm,nn,oo) = logical_post;
                }
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i32_7d( flcl::view_i32_7d_t **v_array_i32_7d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i32_7d = **v_array_i32_7d;
    for (size_t ii = 0; ii < array_i32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i32_7d.extent(6); oo++) {
                  *c_sum += array_i32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i32_7d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i32_7d.extent(6); oo++) {
                  array_i32_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  *c_sum += array_i32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_i64_7d( flcl::view_i64_7d_t **v_array_i64_7d, size_t *f_sum, size_t *c_sum ) {
    *c_sum = 0;
    auto array_i64_7d = **v_array_i64_7d;
    for (size_t ii = 0; ii < array_i64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i64_7d.extent(6); oo++) {
                  *c_sum += array_i64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    if ( *c_sum != *f_sum ) {
      std::cout << "FAILED C kokkos_allocate_view_i64_7d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_i64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_i64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_i64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_i64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_i64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_i64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_i64_7d.extent(6); oo++) {
                  array_i64_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  *c_sum += array_i64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r32_7d( flcl::view_r32_7d_t **v_array_r32_7d, float *f_sum, float *c_sum ){
    *c_sum = 0;
    auto array_r32_7d = **v_array_r32_7d;
    for (size_t ii = 0; ii < array_r32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r32_7d.extent(6); oo++) {
                  *c_sum += array_r32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_single * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r32_7d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r32_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r32_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r32_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r32_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r32_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r32_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r32_7d.extent(6); oo++) {
                  array_r32_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  *c_sum += array_r32_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;
  }

  flcl_test_error_t c_test_kokkos_allocate_view_r64_7d( flcl::view_r64_7d_t **v_array_r64_7d, double *f_sum, double *c_sum ) {
    *c_sum = 0;
    auto array_r64_7d = **v_array_r64_7d;
    for (size_t ii = 0; ii < array_r64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r64_7d.extent(6); oo++) {
                  *c_sum += array_r64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    if ( std::fabs(*c_sum - *f_sum) > (precision_double * *c_sum) ) {
      std::cout << "FAILED C kokkos_allocate_view_r64_7d" << std::endl;
      return FLCL_TEST_FAIL;
    }
    *c_sum = 0;
    for (size_t ii = 0; ii < array_r64_7d.extent(0); ii++) {
      for (size_t jj = 0; jj < array_r64_7d.extent(1); jj++) {
        for (size_t kk = 0; kk < array_r64_7d.extent(2); kk++) {
          for (size_t ll = 0; ll < array_r64_7d.extent(3); ll++) {
            for (size_t mm = 0; mm < array_r64_7d.extent(4); mm++) {
              for (size_t nn = 0; nn < array_r64_7d.extent(5); nn++) {
                for (size_t oo = 0; oo < array_r64_7d.extent(6); oo++) {
                  array_r64_7d(ii,jj,kk,ll,mm,nn,oo) = ii+jj+kk+ll+mm+nn+oo;
                  *c_sum += array_r64_7d(ii,jj,kk,ll,mm,nn,oo);
                }
              }
            }
          }
        }
      }
    }
    return FLCL_TEST_PASS;

  }

}
