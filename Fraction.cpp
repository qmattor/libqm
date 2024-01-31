/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:00:52 by qmattor           #+#    #+#             */
/*   Updated: 2024/01/31 13:35:49 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fraction.hpp"
#include "error.hpp"
#include "logging.hpp"
#include <iostream>
namespace libqm {
// private

static FracType max(FracType a, FracType b) {
  return a * (a - b > 0) | b * (b - a >= 0);
}
static FracType min(FracType a, FracType b) {
  return a * (a - b < 0) | b * (b - a <= 0);
}
static int gcd(FracType a, FracType b) {
  if (a == 0 || b == 0)
    return a | b;
  return gcd(max(a, b) - min(a, b), min(a, b));
}

void Frac::reduce() {
  auto tmp = gcd(numerator, denominator);
  numerator /= tmp;
  denominator /= tmp;
}

// public
Frac::Frac() : numerator(0), denominator(1) {}
Frac::Frac(FracType a, FracType b) : numerator(a) {
  if (b == 0)
    QM_exception(std::runtime_error("denominator cannot be 0"));
  denominator = b;
}

Frac::Frac(double decimal) {
  (void)decimal;
  QM_exception(n_imp_exception())
}

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
  ret.numerator = denominator * other.numerator + numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  return ret;
}
Frac Frac::operator+=(const Frac &other) {
  Frac ret;
  ret.numerator = denominator * other.numerator + numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  *this = ret;
  return *this;
}
Frac Frac::operator-(const Frac &other) const {
  Frac ret;
  ret.numerator = denominator * other.numerator - numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  return ret;
}
Frac Frac::operator-=(const Frac &other) {
  Frac ret;
  ret.numerator = denominator * other.numerator - numerator * other.denominator;
  ret.denominator = this->denominator * other.denominator;
  ret.reduce();
  *this = ret;
  return *this;
}

std::istream &operator>>(std::istream &in, Frac &f) {
  QM_exception(n_imp_exception());
  in >> f.numerator;
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
} // namespace libqm
