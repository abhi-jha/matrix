//
// Created by Yi Pan (Institute of Cancer and Genomic Sciences) on 19/03/2018.
//

#ifndef MATRIX_TEST_MATRIX_BLAS_H
#define MATRIX_TEST_MATRIX_BLAS_H

#include "slab/matrix.h"

namespace slab {
TEST(BLASlevel1Test, COPY) {
  Matrix<double, 1> m1 = {1, 2, 3}, m1c;
  Matrix<float, 1> m2 = {1, 2, 3}, m2c;

  blas_copy(m1, m1c);
  blas_copy(m2, m2c);

  EXPECT_EQ(1, m1c(0));
  EXPECT_EQ(2, m1c(1));
  EXPECT_EQ(3, m1c(2));

  EXPECT_EQ(1, m2c(0));
  EXPECT_EQ(2, m2c(1));
  EXPECT_EQ(3, m2c(2));
}

TEST(BLASlevel1Test, IAMAX) {
  Matrix<double, 1> m1 = {1, 3, 2};
  Matrix<float, 1> m2 = {1, 3, 2};

  auto idx1 = blas_iamax(m1);
  auto idx2 = blas_iamax(m2);

  EXPECT_EQ(1, idx1);
  EXPECT_EQ(1, idx2);
}


}

#endif //MATRIX_TEST_MATRIX_BLAS_H