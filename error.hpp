/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:04:35 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/20 21:02:33 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Quincy Mattor
// Copyright 2023

#include <exception>
#include <string.h>

#ifndef __QM_ERROR__
#define __QM_ERROR__

namespace libqm {

#define QM_exception(exception)                                                \
  {                                                                            \
    libqm::log("Exception thrown at line %i in file %s\n", __LINE__,           \
               __FILE__);                                                      \
    throw(exception);                                                          \
  }

class errno_exception : public std::exception {
private:
  int errnum;

public:
  errno_exception(int err);
  const char *what() const noexcept;
};

class n_imp_exception : public std::exception {
  const char *what() const noexcept;
};

} // namespace libqm
#endif
