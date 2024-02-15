// Quincy Mattor
// Copyright 2023

#include "timer.hpp"

namespace libqm {

void stopwatch::reset() {
  this->start_time = clock();
  this->prior_accum = 0;
}

void stopwatch::pause() {
  if (this->is_paused) return;
  this->prior_accum += clock() - this->start_time;
  this->is_paused = true;
}

void stopwatch::resume() {
  if (!this->is_paused) return;
  this->start_time = clock();
  this->is_paused = false;
}

double stopwatch::get_sec() const {
  if (this->is_paused)
    return static_cast<double>(this->prior_accum) / CLOCKS_PER_SEC;
  else
    return static_cast<double>((clock() - this->start_time) +
                               this->prior_accum) /
           CLOCKS_PER_SEC;
}

double stopwatch::get_min() const {
  if (this->is_paused)
    return static_cast<double>(this->prior_accum) / (CLOCKS_PER_SEC * 60);
  else
    return static_cast<double>((clock() - this->start_time) +
                               this->prior_accum) /
           (CLOCKS_PER_SEC * 60);
}

int stopwatch::get_ticks() const {
  return (clock() - this->start_time) + this->prior_accum;
}
}  // namespace libqm
