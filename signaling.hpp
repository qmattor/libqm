/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signaling.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:05:40 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/25 14:50:34 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

// #define SIGHUP 1  /* Hangup the process */
// #define SIGINT 2  /* Interrupt the process */
// #define SIGQUIT 3 /* Quit the process */
// #define SIGILL 4  /* Illegal instruction. */
// #define SIGTRAP 5 /* Trace trap. */
// #define SIGABRT 6 /* Abort. */

class signal_handler {
protected:
  virtual bool handler(int sig);
  // blank handlers that should get overridden
  virtual void handle_SIGHUP() {}
  virtual void handle_SIGINT() {}
  virtual void handle_SIGQUIT() {}
  virtual void handle_SIGILL() {}
  virtual void handle_SIGTRAP() {}
  virtual void handle_SIGABRT() {}
};
