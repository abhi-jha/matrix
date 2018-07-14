//
// Copyright 2018 The StatsLabs Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// -----------------------------------------------------------------------------
// operations.h
// -----------------------------------------------------------------------------
//
#ifndef SLAB_MATRIX_OPERATIONS_H_
#define SLAB_MATRIX_OPERATIONS_H_

#include <cstddef>
#include <algorithm>
#include <type_traits>
#include "slab/matrix/matrix.h"
#include "slab/matrix/traits.h"

#include <iostream>
using namespace std;

// Scalar Addtion
//
// res = X + val or res = val + X

template<typename T, std::size_t N>
Matrix<T, N> operator+(const Matrix<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res += val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const MatrixRef<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res += val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const T &val, const Matrix<T, N> &x) {
  Matrix<T, N> res = x;
  res += val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const T &val, const MatrixRef<T, N> &x) {
  Matrix<T, N> res = x;
  res += val;
  return res;
}

// Scalar Subtraction
//
// res = X - val

template<typename T, std::size_t N>
Matrix<T, N> operator-(const Matrix<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res -= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator-(const MatrixRef<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res -= val;
  return res;
}

// Scalar Multiplication
//
// res = X * val or res = val * X

template<typename T, std::size_t N>
Matrix<T, N> operator*(const Matrix<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res *= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const MatrixRef<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res *= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const T &val, const Matrix<T, N> &x) {
  Matrix<T, N> res = x;
  res *= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const T &val, const MatrixRef<T, N> &x) {
  Matrix<T, N> res = x;
  res *= val;
  return res;
}

// Scalar Division
//
// res = X / val

template<typename T, std::size_t N>
Matrix<T, N> operator/(const Matrix<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res /= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator/(const MatrixRef<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res /= val;
  return res;
}

// Scalar Modulus
//
// res = X % val

template<typename T, std::size_t N>
Matrix<T, N> operator%(const Matrix<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res %= val;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator%(const MatrixRef<T, N> &x, const T &val) {
  Matrix<T, N> res = x;
  res %= val;
  return res;
}

// Matrix Addtion
//
// res = A + B

template<typename T, std::size_t N>
Matrix<T, N> operator+(const Matrix<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res += b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const MatrixRef<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res += b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const Matrix<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res += b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator+(const MatrixRef<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res += b;
  return res;
}

// Matrix Subtraction
//
// res = A - B

template<typename T, std::size_t N>
Matrix<T, N> operator-(const Matrix<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res -= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator-(const MatrixRef<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res -= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator-(const Matrix<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res -= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator-(const MatrixRef<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res -= b;
  return res;
}

// Element-wise Multiplication
//
// res = A * B

template<typename T, std::size_t N>
Matrix<T, N> operator*(const Matrix<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res *= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const MatrixRef<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res *= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const Matrix<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res *= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator*(const MatrixRef<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res *= b;
  return res;
}

// Element-wise Division
//
// res = A / B

template<typename T, std::size_t N>
Matrix<T, N> operator/(const Matrix<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res /= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator/(const MatrixRef<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res /= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator/(const Matrix<T, N> &a, const MatrixRef<T, N> &b) {
  Matrix<T, N> res = a;
  res /= b;
  return res;
}

template<typename T, std::size_t N>
Matrix<T, N> operator/(const MatrixRef<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res /= b;
  return res;
}

// Computes a matrix-vector product using a general matrix
//
// The operation is defined as
//
// y := Ax
//
// where:
// x and y are vectors,
// A is an m-by-n matrix.
template<typename T>
Matrix<T, 1> matmul(const Matrix<T, 2> &a, const Matrix<T, 1> &x) {
  assert(a.extent(1) == x.extent(0));
  const int m = a.rows();
  const int n = a.cols();
  const int lda = n;
  const int incx = 1;
  const int incy = 1;

  Matrix<T, 1> y(m);

  if (is_double<T>::value) {
    cblas_dgemv(
        CblasRowMajor,             // Layout: row-major (CblasRowMajor) or column-major (CblasColMajor).
        CblasNoTrans,              // trans : CblasNoTrans/CblasTrans/CblasTrans.
        m,                         // m     : the number of rows of the matrix A.
        n,                         // n     : the number of cols of the matrix A.
        (const double) 1.0,        // alpha : the scalar alpha.
        (const double *) a.data(), // a     : the matrix A.
        lda,                       // lda   : the leading dimension of a.
        (const double *) x.data(), // x     : the vector x.
        incx,                      // incx  : the increment for the elements of x.
        (const double) 0.0,        // beta  : the scalar beta.
        (double *) y.data(),       // y     : the vector y.
        incy                       // incy  : the increment for the elements of y.
    );
  } else if (is_float<T>::value) {
    cblas_sgemv(
        CblasRowMajor,
        CblasNoTrans,
        m,
        n,
        (const float) 1.0,
        (const float *) a.data(),
        lda,
        (const float *) x.data(),
        incx,
        (const float) 0.0,
        (float *) y.data(),
        incy
    );
  } else if (is_complex_double<T>::value) {

  } else if (is_complex_float<T>::value) {

  } else {
    for (std::size_t i = 0; i != m; ++i) {
      for (std::size_t j = 0; j != n; ++j) {
        y(i) += a(i, j) * x(j);
      }
    }
  }

  return y;
}

// Computes a matrix-matrix product with general matrices.
//
// The operation is defined as
//
// C := op(A)*op(B),
//
// where:
// op(X) is one of op(X) = X, or op(X) = X^T, or op(X) = X^H,
// A, B and C are matrices:
// op(A) is an m-by-k matrix,
// op(B) is a k-by-n matrix,
// C is an m-by-n matrix.
template<typename T>
Matrix<T, 2> matmul(const Matrix<T, 2> &a, const Matrix<T, 2> &b) {
  assert(a.extent(1) == b.extent(0));

  const int m = a.rows();
  const int n = b.cols();
  const int k = a.cols();

  const int lda = a.cols();
  const int ldb = b.cols();
  const int ldc = b.cols();

  Matrix<T, 2> c(m, n);

  if (is_double<T>::value) {
    cblas_dgemm(
        CblasRowMajor,             // Layout: row-major (CblasRowMajor) or column-major (CblasColMajor).
        CblasNoTrans,              // transa: CblasNoTrans/CblasTrans/CblasConjTrans.
        CblasNoTrans,              // transb: CblasNoTrans/CblasTrans/CblasConjTrans.
        m,                         // m     : the number of rows of the matrix op(A) and of the matrix C.
        n,                         // n     : the number of cols of the matrix op(B) and of the matrix C.
        k,                         // k     : the number of cols of the matrix op(A) and the number of rows of the matrix op(B).
        (const double) 1.0,        // alpha : the scalar alpha.
        (const double *) a.data(), // a     : the matrix A.
        lda,                       // lda   : the leading dimension of a.
        (const double *) b.data(), // b     : the matrix B.
        ldb,                       // ldb   : the leading dimension of b.
        (const double) 0.0,        // beta  : the scalar beta.
        (double *) c.data(),       // c     : the matrix C.
        ldc                        // ldc   : the leading dimension of c.
    );
  } else if (is_float<T>::value) {
    cblas_sgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        m,
        n,
        k,
        (const float) 1.0,
        (const float *) a.data(),
        lda,
        (const float *) b.data(),
        ldb,
        (const float) 0.0,
        (float *) c.data(),
        ldc
    );
  } else if (is_complex_double<T>::value) {

  } else if (is_complex_float<T>::value) {

  } else {
    for (std::size_t i = 0; i != m; ++i) {
      for (std::size_t j = 0; j != n; ++j) {
        for (std::size_t idx = 0; idx != k; ++idx) {
          c(i, j) += a(i, idx) * b(idx, j);
        }
      }
    }
  }

  return c;
}

template<typename T, std::size_t N, typename... Args>
auto reshape(const Matrix<T, N> &a, Args... args) -> decltype(Matrix<T, sizeof...(args)>()) {
  Matrix<T, sizeof...(args)> res(args...);

  if (is_double<T>::value)
    cblas_dcopy(
        a.size(),
        (double *) a.data(),
        1,
        (double *) res.data(),
        1
    );
  else if (is_float<T>::value)
    cblas_scopy(
        a.size(),
        (float *) a.data(),
        1,
        (float *) res.data(),
        1
    );

  return res;
}

template<typename T>
Matrix<T, 2> transpose(const Matrix<T, 2> &a) {
  Matrix<T, 2> res(a.cols(), a.rows());
  for (std::size_t i = 0; i < a.rows(); ++i) {
    for (std::size_t j = 0; j < a.rows(); ++j) {
      res(j, i) = a(i, j);
    }
  }

  return res;
}

#endif // SLAB_MATRIX_OPERATIONS_H_