// Quincy Mattor
// Copyright 2023

#include "error.hpp"

namespace libqm {
errno_exception::errno_exception(int err) : errnum(err) {}

const char *errno_exception::what() const noexcept {
  return strerror(this->errnum);
}
const char *n_imp_exception::what() const noexcept {
  return "this feature has not been implimented";
}

} // namespace libqm
