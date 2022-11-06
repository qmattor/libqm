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

void timer::reset() {
  this->start_time = clock();
  this->prior_accum = 0;
}

void timer::pause() {
  if (this->is_paused) return;
  this->prior_accum += clock() - this->start_time;
  this->is_paused = true;
}

void timer::resume() {
  if (!this->is_paused) return;
  this->start_time = clock();
  this->is_paused = false;
}

double timer::get_sec() const {
  if (this->is_paused)
    return static_cast<double>(this->prior_accum) / CLOCKS_PER_SEC;
  else
    return static_cast<double>((clock() - this->start_time) +
                               this->prior_accum) /
           CLOCKS_PER_SEC;
}

double timer::get_min() const {
  if (this->is_paused)
    return static_cast<double>(this->prior_accum) / (CLOCKS_PER_SEC * 60);
  else
    return static_cast<double>((clock() - this->start_time) +
                               this->prior_accum) /
           (CLOCKS_PER_SEC * 60);
}

int timer::get_ticks() const {
  return (clock() - this->start_time) + this->prior_accum;
}

}  // namespace libqm

#endif  // TIMER_HPP_
