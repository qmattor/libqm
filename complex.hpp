/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:05:47 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/15 16:00:38 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iostream>
#include <string>

#include "fraction.hpp"
namespace libqm {
typedef Frac CType;

class complex {
 public:
  CType r;
  CType c;
  complex(CType r = 0, CType c = 0);

  bool operator==(const complex &rhs) const;
  bool operator!=(const complex &rhs) const;
  bool operator==(complex &rhs) const;
  bool operator!=(complex &rhs) const;
  complex operator+(const complex &rhs);
  complex operator-(const complex &rhs);
  complex operator*(const complex &rhs);
  complex operator/(const complex &rhs);
  complex operator+=(const complex &rhs);
  complex operator-=(const complex &rhs);
  complex operator*=(const complex &rhs);
  // since sqrt, sin, and cos often return irrational numbers, it means
  // it's not closed. This means we HAVE to leave the fraction type behind.
  // kinda lame :(
  double cos() {
    return (r.to_double() / (sqrt((r * r + c * c).to_double())));
  }
  double sin() {
    return (c.to_double() / (sqrt((r * r + c * c).to_double())));
  }
  double abs() { return sqrt((r * r + c * c).to_double()); }
  std::string polar_form();

  friend std::ostream &operator<<(std::ostream &, const complex);
  friend std::istream &operator>>(std::istream &, complex &);
};
};  // namespace libqm
