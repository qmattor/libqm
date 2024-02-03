/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:52:22 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/02 12:32:54 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"
#include "logging.hpp"
#include <iostream>

namespace libqm {
typedef long FracType;

class Frac {
private:
  FracType numerator;
  FracType denominator;
  void reduce();

public:
  Frac();
  //   Frac(double);
  Frac(int);
  Frac(long);
  Frac(FracType, FracType);
  inline FracType get_numerator() { return numerator; }
  inline FracType get_denominator() { return denominator; }
  inline void set_numerator(FracType n) { numerator = n; }
  inline void set_denominator(FracType d) {
    if (d == 0)
      QM_exception(std::runtime_error("value out of bounds"));
    denominator = d;
  }

  Frac operator=(long);
  Frac operator=(int);
  bool operator==(const Frac other) const;
  bool operator!=(const Frac other) const;
  bool operator<=(const Frac other) const;
  bool operator>=(const Frac other) const;
  bool operator<(const Frac other) const;
  bool operator>(const Frac other) const;

  Frac operator*(const Frac &other) const;
  Frac operator*=(const Frac &other);
  Frac operator/(const Frac &other) const;
  Frac operator/=(const Frac &other);
  Frac operator+(const Frac &other) const;
  Frac operator+=(const Frac &other);
  Frac operator-(const Frac &other) const;
  Frac operator-=(const Frac &other);

  Frac operator*(long) const;
  Frac operator*=(long);
  Frac operator/(long) const;
  Frac operator/=(long);
  Frac operator+(long) const;
  Frac operator+=(long);
  Frac operator-(long) const;
  Frac operator-=(long);

  Frac operator*(int) const;
  Frac operator*=(int);
  Frac operator/(int) const;
  Frac operator/=(int);
  Frac operator+(int) const;
  Frac operator+=(int);
  Frac operator-(int) const;
  Frac operator-=(int);

  //   friend funcs
  // form of x/y
  friend std::istream &operator>>(std::istream &, Frac &);
  friend std::ostream &operator<<(std::ostream &, const Frac &);
};
} // namespace libqm
