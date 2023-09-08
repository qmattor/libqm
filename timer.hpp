// Quincy Mattor
// Copyright 2022

#include <ctime>

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace libqm {
class timer {
 protected:
  clock_t prior_accum;
  clock_t start_time;
  bool is_paused;

 public:
  timer() : prior_accum(0), start_time(clock()), is_paused(true) {}
  void pause();
  void resume();
  void reset();
  bool get_is_paused() const { return this->is_paused; }
  double get_sec() const;
  double get_min() const;
  int get_ticks() const;
};

}  // namespace libqm

#endif  // TIMER_HPP_
