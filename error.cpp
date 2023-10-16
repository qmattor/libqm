// Quincy Mattor
// Copyright 2023

#include "error.hpp"

namespace libqm {
errno_exception::errno_exception(int err) : errno(err) {}

// alright this is kinda painful, theres 100ish of these
// and I don't care that much to write them all
const char *errno_exception::what() const noexcept {
  switch (this->errno) {
  case 1:
    return "Operation not permitted.";
  case 2:
    return "No such file or directory.";
  case 3:
    return "No such process.";
  case 4:
    return "Interrupted function call";
  case 5:
    return "Input/output error.";
  case 6:
    return "No such device or address.";
  case 7:
    return "Arg list too long.";
  case 8:
    return "Exec format error.";
  case 9:
    return "Bad file descriptor.";
  case 10:
    return "No child processes.";
  case 11:
    return "Resource deadlock avoided.";
  case 12:
    return "Cannot allocate memory";
  case 13:
    return "Permission denied.";
  case 14:
    return "Bad address.";
  case 15:
    return "Not a block device.";
  case 16:
    return "Resource busy.";
  case 17:
    return "File exists.";
  case 18:
    return "Improper link.";
  case 19:
    return "Operation not supported by device.";
  case 20:
    return "Not a directory.";
  case 21:
    return "Is a directory.";
  case 23:
    return "Invalid argument.";
  default:
    return "probably some value I didn't write down";
  }
}
const char *n_imp_exception::what() const noexcept {
  return "this feature has not been implimented";
}

} // namespace libqm
