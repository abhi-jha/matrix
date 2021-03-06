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
// matrix_ref.h
// -----------------------------------------------------------------------------
//
#ifndef SLAB_MATRIX_MATRIX_REF_H_
#define SLAB_MATRIX_MATRIX_REF_H_

#include <cstddef>
#include <iterator> // std::forward_iterator_tag
#include "slab/matrix/matrix.h"
#include "slab/matrix/matrix_base.h"

template<typename T, std::size_t N>
class MatrixRefIterator;

template<typename T, std::size_t N>
class MatrixRef : public MatrixBase<T, N> {
 public:
  using iterator = MatrixRefIterator<T, N>;
  using const_iterator = MatrixRefIterator<const T, N>;

  MatrixRef() = delete;
  MatrixRef(MatrixRef &&) = default;                 // move
  MatrixRef &operator=(MatrixRef &&) = default;
  MatrixRef(MatrixRef const &) = default;            // copy
  MatrixRef &operator=(MatrixRef const &) = default;
  ~MatrixRef() = default;

  template<typename U>
  MatrixRef(const Matrix<U, N> &);                   // construct from Matrix
  template<typename U>
  MatrixRef &operator=(const Matrix<U, N> &);        // assign from Matrix

  MatrixRef &operator=(MatrixInitializer<T, N>);     // assign from list

  MatrixRef(const MatrixSlice<N> &s, T *p) : MatrixBase<T, N>{s}, ptr_{p} {}

  // total number of elements
  std::size_t size() const { return this->desc_.size; }

  T *data() { return ptr_; }                         // "flat" element access
  const T *data() const { return ptr_; }

  // m(i,j,k) subscripting with integers
  template<typename... Args>
  Enable_if<matrix_impl::Requesting_element<Args...>(), T &>
  operator()(Args... args) {
    return MatrixBase<T,N>::template operator()<Args...>(args...);
  }

  template<typename... Args>
  Enable_if<matrix_impl::Requesting_element<Args...>(), const T &>
  operator()(Args... args) const {
    return MatrixBase<T,N>::template operator()<Args...>(args...);
  }

  // m(s1, s2, s3) subscripting with slides
  template<typename... Args>
  Enable_if<matrix_impl::Requesting_slice<Args...>(), MatrixRef<T, N>>
  operator()(const Args &... args);

  template<typename... Args>
  Enable_if<matrix_impl::Requesting_slice<Args...>(), const MatrixRef<T, N>>
  operator()(const Args &... args) const;

  // m[i] row access
  MatrixRef<T, N - 1> operator[](std::size_t i) { return row(i); }
  MatrixRef<const T, N - 1> operator[](std::size_t i) const { return row(i); }

  // row access
  MatrixRef<T, N - 1> row(std::size_t n);
  MatrixRef<const T, N - 1> row(std::size_t n) const;

  // column access
  MatrixRef<T, N - 1> col(std::size_t n);
  MatrixRef<const T, N - 1> col(std::size_t n) const;

  template<typename F>
  MatrixRef &apply(F f);                             // f(x) for every element x

  // f(x, mx) for corresponding elements of *this and m
  template<typename M, typename F>
  Enable_if<Matrix_type<M>(), MatrixRef &>
  apply(const M &m, F f);

  MatrixRef &operator=(const T &value);              // assignment with scalar

  MatrixRef &operator+=(const T &value);             // scalar addition
  MatrixRef &operator-=(const T &value);             // scalar subtraction
  MatrixRef &operator*=(const T &value);             // scalar multiplication
  MatrixRef &operator/=(const T &value);             // scalar division
  MatrixRef &operator%=(const T &value);             // scalar modulo

  // matrix addition
  template<typename M>
  Enable_if<Matrix_type<M>(), MatrixRef &> operator+=(const M &x);
  // matrix subtraction
  template<typename M>
  Enable_if<Matrix_type<M>(), MatrixRef &> operator-=(const M &x);
  // element-wise multiplication
  template<typename M>
  Enable_if<Matrix_type<M>(), MatrixRef &> operator*=(const M &x);
  // element-wise division
  template<typename M>
  Enable_if<Matrix_type<M>(), MatrixRef &> operator/=(const M &x);
  // element-wise modulus
  template<typename M>
  Enable_if<Matrix_type<M>(), MatrixRef &> operator%=(const M &x);

  iterator begin() { return {this->desc_, ptr_}; }
  const_iterator begin() const { return {this->desc_, ptr_}; }
  iterator end() { return {this->desc_, ptr_, true}; }
  const_iterator end() const { return {this->desc_, ptr_, true}; }

 private:
  T *ptr_;
};

template<typename T, std::size_t N>
template<typename U>
MatrixRef<T, N>::MatrixRef(const Matrix<U, N> &x)
    : MatrixBase<T, N>{x.descriptor()}, ptr_(x.data()) {
}

template<typename T, std::size_t N>
template<typename U>
MatrixRef<T, N> &MatrixRef<T, N>::operator=(const Matrix<U, N> &x) {
  static_assert(Convertible<U, T>(), "MatrixRef =: incompatible element types");
  assert(this->desc_.extents == x.descriptor().extents);

  std::copy(x.begin(), x.end(), begin());
  return *this;
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator=(MatrixInitializer<T, N> init) {
  //std::array<std::size_t, N> extents = matrix_impl::derive_extents<N>(init);
  assert(matrix_impl::derive_extents<N>(init) == this->desc_.extents);

  auto iter = begin();
  matrix_impl::copy_flat(init, iter);

  return *this;
}

template<typename T, size_t N>
template<typename... Args>
Enable_if<matrix_impl::Requesting_slice<Args...>(), MatrixRef<T, N>>
MatrixRef<T, N>::operator()(const Args &... args) {
  MatrixSlice<N> d;
  d.start = this->desc_.start + matrix_impl::do_slice(this->desc_, d, args...);
  d.size = matrix_impl::compute_size(d.extents);
  return {d, data()};
}

template<typename T, size_t N>
template<typename... Args>
Enable_if<matrix_impl::Requesting_slice<Args...>(), const MatrixRef<T, N>>
MatrixRef<T, N>::operator()(const Args &... args) const {
  MatrixSlice<N> d;
  d.start = this->desc_.start + matrix_impl::do_slice(this->desc_, d, args...);
  d.size = matrix_impl::compute_size(d.extents);
  return {d, data()};
}

// row
template<typename T, size_t N>
MatrixRef<T, N - 1> MatrixRef<T, N>::row(size_t n) {
  assert(n < this->n_rows());
  MatrixSlice<N - 1> row;
  matrix_impl::slice_dim<0>(n, this->desc_, row);
  return {row, ptr_};
}

template<typename T, size_t N>
MatrixRef<const T, N - 1> MatrixRef<T, N>::row(size_t n) const {
  assert(n < this->n_rows());
  MatrixSlice<N - 1> row;
  matrix_impl::slice_dim<0>(n, this->desc_, row);
  return {row, ptr_};
}

// col
template<typename T, size_t N>
MatrixRef<T, N - 1> MatrixRef<T, N>::col(size_t n) {
  assert(n < this->cols());
  MatrixSlice<N - 1> col;
  matrix_impl::slice_dim<1>(n, this->desc_, col);
  return {col, ptr_};
}

template<typename T, size_t N>
MatrixRef<const T, N - 1> MatrixRef<T, N>::col(size_t n) const {
  assert(n < this->cols());
  MatrixSlice<N - 1> col;
  matrix_impl::slice_dim<1>(n, this->desc_, col);
  return {col, ptr_};
}

template<typename T, std::size_t N>
template<typename F>
MatrixRef<T, N> &MatrixRef<T, N>::apply(F f) {
  for (auto iter = begin(); iter != end(); ++iter)
    f(*iter);
  return *this;
}

template<typename T, std::size_t N>
template<typename M, typename F>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::apply(const M &m, F f) {
  assert(same_extents(this->desc_, m.descriptor()));
  auto j = m.begin();
  for (auto i = begin(); i != end(); ++i) {
    f(*i, *j);
    ++j;
  }

  return *this;
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator+=(const T &val) {
  return apply([&](T &a) { a += val; });
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator-=(const T &val) {
  return apply([&](T &a) { a -= val; });
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator*=(const T &val) {
  return apply([&](T &a) { a *= val; });
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator/=(const T &val) {
  return apply([&](T &a) { a /= val; });
}

template<typename T, std::size_t N>
MatrixRef<T, N> &MatrixRef<T, N>::operator%=(const T &val) {
  return apply([&](T &a) { a %= val; });
}

template<typename T, std::size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::operator+=(const M &m) {
  //static_assert(m.order_ == N, "+=: mismatched Matrix dimensions");
  assert(same_extents(this->desc_, m.descriptor()));  // make sure sizes match

  return apply(m, [&](T &a, const Value_type<M> &b) { a += b; });
}

template<typename T, std::size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::operator-=(const M &m) {
  //static_assert(m.order_ == N, "+=: mismatched Matrix dimensions");
  assert(same_extents(this->desc_, m.descriptor()));  // make sure sizes match

  return apply(m, [&](T &a, const Value_type<M> &b) { a -= b; });
}

template<typename T, std::size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::operator*=(const M &m) {
  assert(same_extents(this->desc_, m.descriptor()));  // make sure sizes match

  return apply(m, [&](T &a, const Value_type<M> &b) { a *= b; });
}

template<typename T, std::size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::operator/=(const M &m) {
  assert(same_extents(this->desc_, m.descriptor()));  // make sure sizes match

  return apply(m, [&](T &a, const Value_type<M> &b) { a /= b; });
}

template<typename T, std::size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), MatrixRef<T, N> &> MatrixRef<T, N>::operator%=(const M &m) {
  assert(same_extents(this->desc_, m.descriptor()));  // make sure sizes match

  return apply(m, [&](T &a, const Value_type<M> &b) { a %= b; });
}

template<typename T>
class MatrixRef<T, 0> {
 public:
  static constexpr size_t order_ = 0;
  using value_type = T;

  MatrixRef(const MatrixSlice<0> &s, T *p) : ptr_{p + s.start} {}

  T &operator()() { return *ptr_; };
  const T &operator()() const { return *ptr_; }

  operator T &() { return *ptr_; }
  operator const T &() const { return *ptr_; }

 private:
  T *ptr_;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const MatrixRef<T, 0> &mr0) {
  return os << (const T &) mr0;
}

template<typename T, std::size_t N>
class MatrixRefIterator {
  template<typename U, size_t NN>
  friend std::ostream &operator<<(std::ostream &os, const MatrixRefIterator<U, NN> &iter);

 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = typename std::remove_const<T>::type;
  using pointer = T *;
  using reference = T &;
  using difference_type = std::ptrdiff_t;

  MatrixRefIterator(const MatrixSlice<N> &s, T *base, bool limit = false);
  MatrixRefIterator &operator=(const MatrixRefIterator &);

  const MatrixSlice<N> &descriptor() const { return desc_; }

  T &operator*() { return *ptr_; }
  T *operator->() { return ptr_; }

  const T &operator*() const { return *ptr_; }
  const T *operator->() const { return ptr_; }

  MatrixRefIterator &operator++();
  MatrixRefIterator operator++(int);

 private:
  void increment();

  std::array<size_t, N> indx_;
  const MatrixSlice<N> &desc_;
  T *ptr_;
};

template<typename T, std::size_t N>
MatrixRefIterator<T, N>::MatrixRefIterator(const MatrixSlice<N> &s, T *base, bool limit)
    : desc_(s) {
  std::fill(indx_.begin(), indx_.end(), 0);

  if (limit) {
    indx_[0] = desc_.extents[0];
    ptr_ = base + desc_.offset(indx_);
  } else {
    ptr_ = base + s.start;
  }
}

template<typename T, std::size_t N>
MatrixRefIterator<T, N> &MatrixRefIterator<T, N>::operator=(const MatrixRefIterator &iter) {
  std::copy(iter.indx_.begin(), iter.indx_.end(), indx_.begin());
  ptr_ = iter.ptr_;

  return *this;
}

template<typename T, std::size_t N>
MatrixRefIterator<T, N> &
MatrixRefIterator<T, N>::operator++() {
  increment();
  return *this;
}

template<typename T, std::size_t N>
MatrixRefIterator<T, N>
MatrixRefIterator<T, N>::operator++(int) {
  MatrixRefIterator<T, N> x = *this;
  increment();
  return *x;
}

template<typename T, std::size_t N>
void MatrixRefIterator<T, N>::increment() {
  std::size_t d = N - 1;

  while (true) {
    ptr_ += desc_.strides[d];
    ++indx_[d];

    if (indx_[d] != desc_.extents[d]) break;

    if (d != 0) {
      ptr_ -= desc_.strides[d] * desc_.extents[d];
      indx_[d] = 0;
      --d;
    } else {
      break;
    }
  }
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &os, const MatrixRefIterator<T, N> &iter) {
  os << "target: " << *iter.ptr_ << ", indx: " << iter.indx_ << std::endl;
  return os;
}

template<typename T, std::size_t N>
inline bool
operator==(const MatrixRefIterator<T, N> &a, const MatrixRefIterator<T, N> &b) {
  assert(a.descriptor() == b.descriptor());
  return &*a == &*b;
}

template<typename T, std::size_t N>
inline bool
operator!=(const MatrixRefIterator<T, N> &a, const MatrixRefIterator<T, N> &b) {
  return !(a == b);
}

#endif // SLAB_MATRIX_MATRIX_REF_H_
