/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:00:52 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/15 15:37:56 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fraction.hpp"

#include <cmath>
#include <iostream>

#include "error.hpp"
#include "logging.hpp"
namespace libqm {
// private
static int gcd(FracType a, FracType b) {
  FracType R;
  while ((R = (a % b)) > 0) {
    a = b;
    b = R;
  }
  return b;
}

void Frac::reduce() {
  log(verbosity::DEBUG, "reducing fraction %d/%d\n", numerator, denominator);
  auto tmp = abs(numerator) == abs(denominator)
                 ? abs(numerator)
                 : gcd(abs(numerator), abs(denominator));
  numerator /= tmp;
  denominator /= tmp;
  log(verbosity::DEBUG, "reduced fraction to %d/%d\n", numerator, denominator);
}

// public
#pragma region constructors
Frac::Frac() : numerator(0), denominator(1) {}
Frac::Frac(long a, long b) : numerator(a) {
  if (b == 0) QM_exception(std::runtime_error("value out of bounds"));
  if (b < 0) {
    numerator = -numerator;
    b = -b;
  }
  denominator = b;
  reduce();
}

Frac::Frac(long f) : numerator(f), denominator(1) {}
Frac::Frac(int f) : numerator(f), denominator(1) {}

Frac Frac::operator=(long i) {
  Frac ret(i, 1);
  return ret;
}

Frac Frac::operator=(int i) {
  Frac ret(i, 1);
  return ret;
}

#pragma endregion

// doesn't fit in structure of code so I'm sticking it here
double Frac::to_double() {
  return (((double)numerator) / ((double)denominator));
}

#pragma region comparators
bool Frac::operator==(const Frac other) const {
  return ((numerator == other.numerator && denominator == other.denominator) ||
          (0 == numerator && other.numerator == 0));
}
bool Frac::operator!=(const Frac other) const {
  return (numerator != other.numerator ||
          (denominator != other.denominator && numerator != 0));
}
bool Frac::operator<=(const Frac other) const {
  auto tmp_num = numerator * other.denominator;
  auto tmp_other_num = other.numerator * denominator;
  return tmp_num <= tmp_other_num;
}
bool Frac::operator>=(const Frac other) const {
  auto tmp_num = numerator * other.denominator;
  auto tmp_other_num = other.numerator * denominator;
  return tmp_num >= tmp_other_num;
}
bool Frac::operator<(const Frac other) const {
  auto tmp_num = numerator * other.denominator;
  auto tmp_other_num = other.numerator * denominator;
  return tmp_num > tmp_other_num;
}
bool Frac::operator>(const Frac other) const {
  auto tmp_num = numerator * other.denominator;
  auto tmp_other_num = other.numerator * denominator;
  return tmp_num > tmp_other_num;
}
#pragma endregion

#pragma region ops
Frac Frac::operator*(const Frac &other) const {
  Frac ret;
  ret.numerator = this->numerator * other.numerator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  return ret;
}
Frac Frac::operator*=(const Frac &other) {
  this->numerator *= other.numerator;
  this->denominator *= other.denominator;
  this->reduce();
  return *this;
}
Frac Frac::operator/(const Frac &other) const {
  Frac ret;
  ret.numerator = this->numerator * other.denominator;
  ret.denominator = this->denominator * other.numerator;
  ret.reduce();
  return ret;
}
Frac Frac::operator/=(const Frac &other) {
  this->numerator *= other.denominator;
  this->denominator *= other.numerator;
  this->reduce();
  return *this;
}
Frac Frac::operator+(const Frac &other) const {
  Frac ret;
  ret.numerator =
      denominator * other.numerator + numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  return ret;
}
Frac Frac::operator+=(const Frac &other) {
  Frac ret;
  ret.numerator =
      denominator * other.numerator + numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  *this = ret;
  return *this;
}
Frac Frac::operator-(const Frac &other) const {
  Frac ret(numerator * other.denominator - denominator * other.numerator,
           this->denominator * other.denominator);
  ret.reduce();
  return ret;
}
Frac Frac::operator-=(const Frac &other) {
  Frac ret;
  ret.numerator =
      numerator * other.denominator - denominator * other.numerator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  *this = ret;
  return *this;
}

// form of x/y
std::istream &operator>>(std::istream &in, Frac &f) {
  in >> f.numerator;
  in.get();
  in >> f.denominator;
  return in;
}
std::ostream &operator<<(std::ostream &out, const Frac &f) {
  if (f.denominator == 1)
    out << f.numerator;
  else
    out << f.numerator << "/" << f.denominator;
  return out;
}

Frac Frac::operator*(long l) const {
  Frac f = *this;
  f.numerator *= l;
  f.reduce();
  return f;
}
Frac Frac::operator*=(long l) {
  numerator *= l;
  reduce();
  return *this;
}
Frac Frac::operator/(long l) const {
  Frac f = *this;
  f.denominator *= l;
  f.reduce();
  return f;
}
Frac Frac::operator/=(long l) {
  denominator *= l;
  reduce();
  return *this;
}
Frac Frac::operator+(long l) const {
  Frac f = *this;
  f.numerator += l * f.denominator;
  f.reduce();
  return f;
}
Frac Frac::operator+=(long l) {
  numerator += denominator * l;
  reduce();
  return *this;
}
Frac Frac::operator-(long l) const {
  Frac f = *this;
  f.numerator -= l * f.denominator;
  f.reduce();
  return f;
}
Frac Frac::operator-=(long l) {
  numerator -= denominator * l;
  reduce();
  return *this;
}

Frac Frac::operator*(int i) const {
  Frac f = *this;
  f.numerator *= i;
  f.reduce();
  return f;
}
Frac Frac::operator*=(int i) {
  numerator *= i;
  reduce();
  return *this;
}
Frac Frac::operator/(int i) const {
  Frac f = *this;
  f.denominator *= i;
  f.reduce();
  return f;
}
Frac Frac::operator/=(int i) {
  denominator *= i;
  reduce();
  return *this;
}
Frac Frac::operator+(int i) const {
  Frac f = *this;
  f.numerator += i * f.denominator;
  f.reduce();
  return f;
}
Frac Frac::operator+=(int i) {
  numerator += denominator * i;
  reduce();
  return *this;
}
Frac Frac::operator-(int i) const {
  Frac f = *this;
  f.numerator -= i * f.denominator;
  f.reduce();
  return f;
}
Frac Frac::operator-=(int i) {
  numerator -= denominator * i;
  reduce();
  return *this;
}
#pragma endregion

}  // namespace libqm
