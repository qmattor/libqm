/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_header.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:56:10 by qmattor           #+#    #+#             */
/*   Updated: 2023/12/01 20:31:42 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <pthread.h>
#include <thread>

#ifndef __RW_HEADER__
#define __RW_HEADER__
namespace libqm {

template <int SIZE> class Semaphore {
private:
  // I'm just going to cheat a little here
  pthread_mutex_t m;
  int32_t *var;

public:
  // no copies >:(
  Semaphore(const Semaphore &) = delete;
  Semaphore &operator=(const Semaphore &) = delete;

  Semaphore(int32_t initial_value) {
    pthread_mutex_init(&m, NULL);
    var = new int32_t;
    *var = initial_value;
  }
  ~Semaphore() {
    delete var;
    pthread_mutex_destroy(&m);
    s
  }
  void signal() {
    pthread_mutex_lock(&m);
    *var = *var == 0 ? 0 : (*var) - 1;
    pthread_mutex_unlock(&m);
  }
  void wait() {
    pthread_mutex_lock(&m);
    while (*var >= SIZE) {
      pthread_mutex_unlock(&m);
      // GIVE UP THREAD CONTROL
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      pthread_mutex_lock(&m);
    }
    (*var)++;
    pthread_mutex_unlock(&m);
  }
};

class mutex : private Semaphore<1> {
public:
  mutex() : Semaphore(0) {}
  void lock() { wait(); }
  void unlock() { signal(); }
};
} // namespace libqm

#endif
