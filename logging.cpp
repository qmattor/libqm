/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:04:42 by qmattor           #+#    #+#             */
/*   Updated: 2024/02/12 12:48:28 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Quincy Mattor
// Copyright 2023

#include "logging.hpp"

// gloabal statics
bool is_init = false;
FILE *fp = NULL;
extern int errno;
libqm::verbosity verbosity_level = libqm::verbosity::NORMAL;

namespace libqm {

void init_log() {
  fp = fopen("Log.txt", "w");
  if (fp == NULL) throw errno_exception(errno);
  is_init = true;
}
void init_log(const char *file) {
  fp = fopen(file, "w");
  if (fp == NULL) throw errno_exception(errno);
  is_init = true;
}

void init_log(std::string file) {
  char *tmp = (char *)malloc(sizeof(char) * file.length());
  strcpy(tmp, file.c_str());
  fp = fopen(tmp, "w");
  if (fp == NULL) {
    free(tmp);
    throw errno_exception(errno);
  }
  is_init = true;
  free(tmp);
}

void init_log(FILE *p) {
  fp = p;
  is_init = true;
}

void log(const char *fmt, ...) {
  if (!is_init) return;
  va_list args;
  va_start(args, fmt);
  vfprintf(fp, fmt, args);
  va_end(args);
}

void log(FILE *fd, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(fd, fmt, args);
  va_end(args);
}

void log(FILE *fd, verbosity v, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  if (v <= verbosity_level) vfprintf(fd, fmt, args);
  va_end(args);
}

void log(verbosity v, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  if (v <= verbosity_level) vfprintf(fp, fmt, args);
  va_end(args);
}

void close_log() { fclose(fp); }

void log_setverbosity(verbosity v) { verbosity_level = v; }

}  // namespace libqm
