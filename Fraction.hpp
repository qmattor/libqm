/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:52:22 by qmattor           #+#    #+#             */
/*   Updated: 2024/01/31 13:30:16 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
  Frac(double);
  Frac(FracType, FracType);
  Frac operator*(const Frac &other) const;
  Frac operator*=(const Frac &other);
  Frac operator/(const Frac &other) const;
  Frac operator/=(const Frac &other);
  Frac operator+(const Frac &other) const;
  Frac operator+=(const Frac &other);
  Frac operator-(const Frac &other) const;
  Frac operator-=(const Frac &other);
  friend std::istream &operator>>(std::istream &, Frac &);
  friend std::ostream &operator<<(std::ostream &, const Frac &);
};
} // namespace libqm
