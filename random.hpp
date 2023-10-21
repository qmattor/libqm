/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:03:53 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/19 12:04:24 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Quincy Mattor
// Copyright 2022

#include <stdint.h>

#include <chrono>
#include <climits>
#include <functional>
#include <random>
#include <type_traits>

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

namespace libqm {
// ok, so the gist of what this does is it restricts typing to just ints and
// floats as well as their derivatives. this in essence simplifies the error
// messages to the template declaration and the line it that casued it
template <typename T,
          typename =
              typename std::enable_if<std::is_integral<T>::value ||
                                      std::is_floating_point<T>::value>::type>
class rand_obj {
private:
  std::default_random_engine *generator;
  std::uniform_int_distribution<T> *distribution;

public:
  rand_obj() {
    unsigned int seed =
        std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = new std::default_random_engine(seed);
    this->distribution =
        new std::uniform_int_distribution<T>(SHRT_MIN, SHRT_MAX);
  }

  rand_obj(T min, T max) {
    unsigned int seed =
        std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = new std::default_random_engine(seed);
    this->distribution = new std::uniform_int_distribution<T>(min, max);
  }

  ~rand_obj() {
    delete this->distribution;
    delete this->generator;
  }

  T next_rand() {
    T ret = (*(this->distribution))(*(this->generator));
    return ret;
  }
};
} // namespace libqm

#endif // RANDOM_HPP_
