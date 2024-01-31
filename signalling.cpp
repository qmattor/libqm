/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalling.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:29:16 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/25 14:47:08 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.hpp"
#include "logging.hpp"
#include "signaling.hpp"
#include <exception>

// class signal_handler {
// protected:
//   virtual void handler(int sig);
//   virtual void handle_SIGHUP();
//   virtual void handle_SIGINT();
//   virtual void handle_SIGQUIT();
//   virtual void handle_SIGILL();
//   virtual void handle_SIGTRAP();
//   virtual void handle_SIGABRT();
// };

// #define SIGHUP 1  /* Hangup the process */
// #define SIGINT 2  /* Interrupt the process */
// #define SIGQUIT 3 /* Quit the process */
// #define SIGILL 4  /* Illegal instruction. */
// #define SIGTRAP 5 /* Trace trap. */
// #define SIGABRT 6 /* Abort. */

bool signal_handler::handler(int sig) {
  switch (sig) {
  case SIGHUP:
    handle_SIGHUP();
    return true;
  case SIGINT:
    handle_SIGINT();
    return true;
  case SIGQUIT:
    handle_SIGQUIT();
    return true;
  case SIGILL:
    handle_SIGILL();
    return true;
  case SIGTRAP:
    handle_SIGTRAP();
    return true;
  case SIGABRT:
    handle_SIGABRT();
    return true;
  default:
    QM_exception(std::runtime_error("unhandled signal encountered"));
  }
  return false;
}
