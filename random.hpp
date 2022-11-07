// Quincy Mattor
// Copyright 2022

#include <stdint.h>

#include <chrono>
#include <climits>
#include <functional>
#include <random>
#include <type_traits>

#ifndef QM_RAND_HPP_
#define QM_RAND_HPP_

// rand already exists in global namespace so I don't want to redef
namespace libqm {
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
}  // namespace libqm

#endif  // QM_RAND_HPP_
