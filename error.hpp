// Quincy Mattor
// Copyright 2023

#include <exception>

#ifndef __QM_ERROR__
#define __QM_ERROR__

namespace libqm {
void log(const char *, ...);
void init_log();
void init_log(char *file);
void close_log();

#define QM_exception(exception)                                        \
  {                                                                    \
    log("Exception thrown at line %i in file %s", __LINE__, __FILE__); \
    close_log();                                                       \
    throw(exception);                                                  \
  }

class errno_exception : public std::exception {
 private:
  int errno;

 public:
  errno_exception(int err);
  const char *what() const noexcept;
};
}  // namespace libqm
#endif
