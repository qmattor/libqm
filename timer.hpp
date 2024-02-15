/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:04:18 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/12 12:48:23 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Quincy Mattor
// Copyright 2022

#include <ctime>
#include <functional>

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace libqm {
class stopwatch {
 protected:
  clock_t prior_accum;
  clock_t start_time;
  bool is_paused;

 public:
  stopwatch() : prior_accum(0), start_time(clock()), is_paused(true) {}
  void pause();
  void resume();
  void reset();
  bool get_is_paused() const { return this->is_paused; }
  double get_sec() const;
  double get_min() const;
  int get_ticks() const;
};

/// please be aware, ONLY 1 CAN EXIST AT ANY TIME
class timer {
 public:
  timer(std::function<void(int)> handler);
  timer(std::function<void(int)> handler, uint16_t time);
  timer(std::function<void(int)> handler, uint16_t time, bool start);
  void start();
  void stop();
  void pause();
  void set_interval(uint32_t miliseconds);
};

}  // namespace libqm

#endif  // TIMER_HPP_
