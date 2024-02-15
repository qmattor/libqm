/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:03:45 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/13 00:33:24 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Quincy Mattor
// Copyright 2022

#include <functional>
#include <iostream>
#include <vector>

#include "logging.hpp"

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

namespace libqm {

template <class T>
class matrix {
 protected:
  size_t y;
  size_t x;
  std::vector<T> elements;

 public:
  matrix();  // purely for use of creating blank things to overwrite later
  matrix(size_t x, size_t y);
  matrix(size_t x, size_t y, T init);
  matrix(matrix &&other) noexcept;
  matrix(const matrix &other);
  // ~matrix();
  matrix<T> &operator=(const matrix<T> &other);
  matrix<T> &operator=(matrix<T> &&other) noexcept;
  bool operator!=(const matrix<T> &) const;
  bool operator==(const matrix &other) const;
  // matrix ops
  matrix<T> operator*(const matrix<T> &other);
  matrix<T> operator+(const matrix<T> &other);
  matrix<T> operator-(const matrix<T> &other);
  // scaler ops
  matrix<T> operator*(const T scaler);
  matrix<T> operator*=(const T scaler);
  matrix<T> operator+(const T scaler);
  matrix<T> operator+=(const T scaler);
  matrix<T> operator-(const T scaler);
  matrix<T> operator-=(const T scaler);
  matrix<T> operator/(const T scaler);
  virtual T &operator()(size_t x, size_t y);
  virtual T operator()(size_t x, size_t y) const;
  size_t get_y() const;
  size_t get_x() const;
  size_t get_size() const;
  T &at(size_t x, size_t y);
  T at(size_t x, size_t y) const;
  // if resized, there's no garantee that the data will make sense any more
  bool resize(size_t new_x, size_t new_y);
  bool foreach(std::function<bool(T &)>);
  bool foreach(std::function<bool(size_t, size_t, T &)>);
  bool contains(const T ele) const;
  bool contains(std::function<bool(T)> func) const;
  bool contains(std::function<bool(size_t, size_t, T)>) const;
  T &find(T);

  void row_swap(size_t a, size_t b);
  // row a += b
  void add_rows(size_t a, size_t b);

  void scale_row(size_t a, T scalor);

  template <class Z>
  friend std::istream &operator>>(std::istream &, matrix<Z> &);
  template <class Z>
  friend std::ostream &operator<<(std::ostream &, const matrix<Z> &);
};

template <class T>
matrix<T>::matrix() : y(0), x(0) {}

template <class T>
matrix<T>::matrix(size_t x, size_t y, T init) : y(y), x(x) {
  if (y == 0 || x == 0) throw std::runtime_error("invalid initial size");
  elements.resize(y * x);
  for (T &t : elements) {
    t = init;
  }
}

template <class T>
matrix<T>::matrix(size_t x, size_t y) : y(y), x(x) {
  if (y == 0 || x == 0) throw std::runtime_error("invalid initial size");
  elements.resize(y * x);
}

// template <class T> matrix<T>::~matrix() { delete this->elements; }

template <class T>
matrix<T>::matrix(matrix &&other) noexcept {
  if (other != *this) {
    this->y = other.y;
    this->x = other.x;
    this->elements.swap(other.elements);
  }
}

template <class T>
matrix<T>::matrix(const matrix<T> &other) {
  if (*this != other) {
    this->y = other.y;
    this->x = other.x;
    this->elements.resize(this->y * this->x);
    std::copy(
        other.elements.begin(), other.elements.end(), this->elements.begin());
  }
}

template <class T>
matrix<T> &matrix<T>::operator=(const matrix &other) {
  this->y = other.y;
  this->x = other.x;
  this->elements.resize(this->y * this->x);
  std::copy(
      other.elements.begin(), other.elements.end(), this->elements.begin());
  return *this;
}

template <class T>
matrix<T> &matrix<T>::operator=(matrix &&other) noexcept {
  if (other == *this) return *this;
  this->y = other.y;
  this->x = other.x;
  std::swap(this->elements, other.elements);
  return *this;
}

template <class T>
T &matrix<T>::operator()(size_t x, size_t y) {
  return this->elements.at(y * this->x + x);
}

template <class T>
T matrix<T>::operator()(size_t x, size_t y) const {
  return this->elements.at(y * this->x + x);
}

// const doesn't matter bc by value
template <class T>
size_t matrix<T>::get_y() const {
  return this->y;
}

template <class T>
size_t matrix<T>::get_x() const {
  return this->x;
}

template <class T>
size_t matrix<T>::get_size() const {
  return this->elements.size();
}

// removed temporarily

template <class T>
bool matrix<T>::resize(size_t new_x, size_t new_y) {
  if (new_x == 0 || new_y == 0) return false;

  // fuck it, don't care about maintaining elements in the right spot.
  x = new_x;
  y = new_y;
  elements.resize(x * y);
  return true;
}

template <class T>
T &matrix<T>::at(size_t x, size_t y) {
  if (y >= this->y) throw std::out_of_range("y overflow");
  if (x >= this->x) throw std::out_of_range("x overflow");
  return (*this)(x, y);
}

template <class T>
T matrix<T>::at(size_t x, size_t y) const {
  if (y >= this->y) throw std::out_of_range("y overflow");
  if (x >= this->x) throw std::out_of_range("x overflow");
  return (*this)(x, y);
}

template <class T>
bool matrix<T>::operator!=(const matrix<T> &other) const {
  if (other.y != this->y) return true;
  if (other.x != this->x) return true;
  try {
    for (size_t i = 0; i < this->elements.size(); i++)
      if (this->elements.at(i) != other.elements.at(i)) return true;
  } catch (std::exception &e) {
    return true;
  }
  return false;
}

// std::__vector_base<s_state_node, std::allocator<s_state_node>>::value_type
// std::__vector_base<s_state_node, std::allocator<s_state_node>>::value_type

template <class T>
bool matrix<T>::operator==(const matrix &other) const {
  if (other.y != this->y) return false;
  if (other.x != this->x) return false;
  try {
    for (size_t i = 0; i < this->elements.size(); i++)
      if (!(this->elements.at(i) == other.elements.at(i))) return false;
  } catch (std::out_of_range &e) {
    return false;
  }
  return true;
}

template <class T>
bool matrix<T>::contains(T ele) const {
  log(verbosity::DEBUG, "begining contains\n");
  for (T e : this->elements) {
    if (e == ele) return true;
  }
  log(verbosity::DEBUG, "finishing contains\n");
  return false;
}

template <class T>
bool matrix<T>::contains(std::function<bool(T)> func) const {
  log(verbosity::DEBUG, "begining contains\n");
  for (auto e : this->elements)
    if (func(e)) return true;
  return false;
  log(verbosity::DEBUG, "finishing contains\n");
}

template <class T>
bool matrix<T>::contains(std::function<bool(size_t, size_t, T)> func) const {
  for (size_t j = 0; j < this->y; j++)
    for (size_t i = 0; i < this->x; i++)
      if (func(i, j, this->at(i, j))) return true;
  return false;
}

template <class T>
T &matrix<T>::find(T ele) {
  for (size_t i = 0; i < this->elements.size(); i++)
    if (this->elements.at(i) == ele) return this->elements.at(i);
  throw std::runtime_error("Matrix does not contian element");
}

template <class T>
bool matrix<T>::foreach(std::function<bool(T &)> func) {
  for (size_t j = 0; j < this->y; j++)
    for (size_t i = 0; i < this->x; i++)
      if (!func(this->at(i, j))) return false;
  return true;
}

template <class T>
bool matrix<T>::foreach(std::function<bool(size_t, size_t, T &)> func) {
  for (size_t j = 0; j < this->y; j++)
    for (size_t i = 0; i < this->x; i++)
      if (!func(i, j, this->elements.at(j * this->x + i))) return false;
  return true;
}

template <class T>
std::istream &operator>>(std::istream &in, matrix<T> &m) {
  in >> m.x;
  in >> m.y;
  m.elements.resize(m.x * m.y);
  size_t i = 0;
  while (i < (m.x * m.y)) {
    if (in.peek() == EOF)
      throw std::runtime_error("File EOF found prematurely");
    in >> m.elements.at(i++);
  }
  return in;
}

template <class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
  out << m.x << " " << m.y << "\n";
  for (size_t y = 0; y < m.y; y++) {
    for (size_t x = 0; x < m.x; x++) {
      out << m.elements.at(y * m.x + x) << ", ";
    }
    out << "\n";
  }
  return out;
}

// matrix x matrix operation

// currently only for
// matrix cross product
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y || other.y != this->x)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      size_t y1 = 0;
      T sum = (this->at(0, y) * other(x, y1++));
      for (size_t x1 = 1; x1 < this->x; x1++) {
        sum = sum + ((this->at(x1, y) * other(x, y1++)));
      }
      ret(x, y) = sum;
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      ret(x, y) = this->at(x, y) + other(x, y);
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator-(const matrix<T> &other) {
  if (other.x != this->x || other.y != this->y)
    throw std::runtime_error("Matrix mismatch");
  matrix<T> ret(this->x, this->y);
  for (size_t y = 0; y < this->y; y++) {
    for (size_t x = 0; x < this->x; x++) {
      ret(x, y) = this->at(x, y) - other(x, y);
    }
  }
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator+(const T scaler) {
  matrix<T> ret;
  ret = *this;
  ret.foreach([scaler](T &ele) {
    ele += scaler;
    return true;
  });
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator*(const T scaler) {
  matrix<T> ret;
  ret = *this;
  ret.foreach([scaler](T &ele) {
    ele *= scaler;
    return true;
  });
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator*=(const T scaler) {
  this->foreach([scaler](T &value) {
    value *= scaler;
    return true;
  });
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator+=(const T scaler) {
  this->foreach([scaler](T &value) {
    value += scaler;
    return true;
  });
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator-(const T scaler) {
  matrix<T> ret;
  ret = *this;
  ret.foreach([scaler](T &ele) {
    ele -= scaler;
    return true;
  });
  return ret;
}

template <class T>
matrix<T> matrix<T>::operator-=(const T scaler) {
  this->foreach([scaler](T &value) {
    value -= scaler;
    return true;
  });
  return *this;
}

template <class T>
matrix<T> matrix<T>::operator/(const T scaler) {
  matrix<T> ret;
  ret = *this;
  ret.foreach([&scaler](T &value) {
    value /= scaler;
    return true;
  });
  return ret;
}

template <class T>
void matrix<T>::row_swap(size_t a, size_t b) {
  for (size_t x = 0; x < this->x; x++) {
    T tmp = at(x, a);
    at(x, a) = at(x, b);
    at(x, b) = tmp;
  }
}

template <class T>
void matrix<T>::add_rows(size_t a, size_t b) {
  for (size_t x = 0; x < this->x; x++) {
    at(x, a) += at(x, b);
  }
}

template <class T>
void matrix<T>::scale_row(size_t a, T scalor) {
  for (size_t x = 0; x < this->x; x++) {
    at(x, a) *= scalor;
  }
}

}  // namespace libqm
#endif  // MATRIX_HPP_
