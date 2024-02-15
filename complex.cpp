/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:12:56 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/15 15:34:56 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"

#include <iomanip>
namespace libqm {
// complex::complex() {
//   r = 0;
//   c = 0;
// }

// complex::complex(CType r) {
//   this->r = r;
//   c = 0;
// }
complex::complex(CType r, CType c) : r(r), c(c) {}

bool complex::operator==(const complex &rhs) const {
  // we gotta do a float round here bc yk flo at
  return (this->c == rhs.c && this->r == rhs.r);
}
bool complex::operator!=(const complex &rhs) const {
  return (this->c != rhs.c || this->r != rhs.r);
}

bool complex::operator==(complex &rhs) const {
  return (this->c == rhs.c && this->r == rhs.r);
}
bool complex::operator!=(complex &rhs) const {
  return (this->c != rhs.c || this->r != rhs.r);
}

// def wrong
complex complex::operator+(const complex &rhs) {
  complex c(this->r + rhs.r, this->c + rhs.c);
  return c;
}
complex complex::operator-(const complex &rhs) {
  complex c(this->r - rhs.r, this->c - rhs.c);
  return c;
}

complex complex::operator*(const complex &rhs) {
  complex ret(this->r * rhs.r - (this->c * rhs.c),
              this->r * rhs.c + (this->c * rhs.r));
  return ret;
}

complex complex::operator/(const complex &rhs) {
  // a + ib
  //------
  // c + id
  //  ac + bd     bc - ad
  //  -------  +  -------
  //  cc + dd     cc + dd
  complex c(
      (this->r * rhs.r + this->c * rhs.c) / (rhs.r * rhs.r + rhs.c * rhs.c),
      (this->c * rhs.r - this->r * rhs.c) / (rhs.r * rhs.r + rhs.c * rhs.c));
  return c;
}

complex complex::operator+=(const complex &rhs) {
  this->c += rhs.c;
  this->r += rhs.r;
  return *this;
}
complex complex::operator-=(const complex &rhs) {
  this->c -= rhs.c;
  this->r -= rhs.r;
  return *this;
}

complex complex::operator*=(const complex &rhs) {
  CType r = this->r;
  CType c = this->c;
  this->r = r * rhs.r - (c * rhs.c);
  this->c = r * rhs.c + (c * rhs.r);
  return *this;
}

std::ostream &operator<<(std::ostream &out, const complex c) {
  out << c.r << " + " << c.c << "i";
  return out;
}
std::istream &operator>>(std::istream &in, complex &c) {
  in >> c.r;
  in.get();
  in.get();
  in.get();
  in >> c.c;
  return in;
}

std::string complex::polar_form() {
  std::string ret = "";
  ret += std::to_string(this->abs());
  ret += "e^i";
  ret += std::to_string(this->cos());
  return ret;
}
}  // namespace libqm
