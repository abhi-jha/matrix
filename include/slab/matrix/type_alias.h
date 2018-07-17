#ifndef SLAB_MATRIX_TYPEDEF_H_
#define SLAB_MATRIX_TYPEDEF_H_

#include "slab/matrix/matrix.h"

using vec      = Matrix<double, 1>;
using mat      = Matrix<double, 2>;
using cube     = Matrix<double, 3>;

using dvec     = Matrix<double, 1>;
using dmat     = Matrix<double, 2>;
using dcube    = Matrix<double, 3>;

using fvec     = Matrix<float, 1>;
using fmat     = Matrix<float, 2>;
using fcube    = Matrix<float, 3>;

using cx_vec   = Matrix<std::complex<double>, 1>;
using cx_mat   = Matrix<std::complex<double>, 2>;
using cx_cube  = Matrix<std::complex<double>, 3>;

using cx_dvec  = Matrix<std::complex<double>, 1>;
using cx_dmat  = Matrix<std::complex<double>, 2>;
using cx_dcube = Matrix<std::complex<double>, 3>;

using cx_fvec  = Matrix<std::complex<float>, 1>;
using cx_fmat  = Matrix<std::complex<float>, 2>;
using cx_fcube = Matrix<std::complex<float>, 3>;

using uvec     = Matrix<unsigned, 1>;
using umat     = Matrix<unsigned, 2>;
using ucube    = Matrix<unsigned, 3>;

using ivec     = Matrix<int, 1>;
using imat     = Matrix<int, 2>;
using icube    = Matrix<int, 3>;

#endif // SLAB_MATRIX_TYPEDEF_H_
