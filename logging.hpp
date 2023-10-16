// Quincy Mattor
// copyright 2023

#include "error.hpp"
#include <cstdarg>
#include <stdio.h>
#include <string>

#ifndef __QM_LOGGING__
#define __QM_LOGGING__

namespace libqm {
enum verbosity { NONE = 0, MINIMAL, NORMAL, DEBUG };

void log(const char *, ...);
void log(verbosity v, const char *, ...);
void log(FILE *fd, verbosity v, const char *, ...);
void log(FILE *fd, const char *, ...);
void log_setverbosity(verbosity v);
void init_log();
void init_log(const char *file);
void init_log(std::string file);
void close_log();

#define logNL libqm::log("\n")
#define logDNL libqm::log(libqm::verbosity::DEBUG, "\n")
}; // namespace libqm

#endif
