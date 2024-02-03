/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiprocessing.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:04:30 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/23 12:43:25 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.hpp"
#include "libft/libft.h"
#include <string>
#include <unistd.h>

namespace libqm {

class child_proc {
  friend class parrent_proc;

public:
  child_proc();
  ~child_proc();
  int send(const char *msg);
  int send(std::string msg);
  std::string recieve();
  void kill();
  template <typename F, class... Args> void start(F f, Args... args);

private:
  bool is_child;
  bool in_use;
  int parent_read_fd;
  int parent_write_fd;
  int child_read_fd;
  int child_write_fd;
  int pid;
  int child_pid;
};

class parrent_proc {
  friend class child_proc;

public:
  parrent_proc(child_proc &c) {
    pid = getpid();
    parent_pid = c.pid;
    send_fd = c.child_write_fd;
    recieve_fd = c.parent_read_fd;
    char *tmp = ft_itoa(pid);
    send(tmp);
    free(tmp);
  }
  // so if for whatever reason we have
  ~parrent_proc() { exit(0); }
  int send(const char *msg) {
    log(verbosity::DEBUG, "sending from child:%s\n", msg);
    write(send_fd, msg, ft_strlen(msg));
    write(send_fd, "\31", 1);
    return ft_strlen(msg) + 1;
  }
  int send(std::string msg) {
    const char *dup = ft_strdup(msg.c_str());
    send(dup);
    free((void *)dup);
    return msg.length() + 1;
  }
  std::string recieve() {
    char c;
    std::string ret;
    while (read(recieve_fd, &c, 1)) {
      if (c == '\31') {
        break;
      } else if (c == '\4') {
        exit(0);
      } else {
        ret.push_back(c);
      }
    }
    return ret;
  }

private:
  int pid;
  int parent_pid;
  int recieve_fd;
  int send_fd;
};

#define FORK(func)                                                             \
  {                                                                            \
    int pid = fork();                                                          \
    if (pid < 0) {                                                             \
      perror(strerror(errno));                                                 \
      exit(-1);                                                                \
    }                                                                          \
    if (pid == 0)                                                              \
      func;                                                                    \
  }

#define PIPE(x)                                                                \
  {                                                                            \
    if (pipe(x) < 0) {                                                         \
      perror(strerror(errno));                                                 \
      exit(-1);                                                                \
    }                                                                          \
  }

child_proc::child_proc() {
  int fd[4];
  PIPE(fd);
  PIPE(&(fd[2]));
  this->parent_read_fd = fd[0];
  this->parent_write_fd = fd[1];
  this->child_read_fd = fd[2];
  this->child_write_fd = fd[3];
  in_use = false;
  is_child = false;
  pid = getpid();
}

template <typename F, class... Args> void child_proc::start(F f, Args... args) {
  if (in_use)
    QM_exception(std::runtime_error("Process is already in use"));
  in_use = true;
  int pid = fork();
  if (pid < 0) {
    perror(strerror(errno));
    exit(-1);
  }
  if (pid == 0) {
    log(verbosity::DEBUG, "starting child process\n");
    this->is_child = true;
    log(verbosity::DEBUG, "starting child main\n");

    f(parrent_proc(*this), args...);
    auto tmp = recieve();
    child_pid = std::stoi(tmp);
    log(verbosity::DEBUG, "exiting child main\n");
    exit(0);
  }
  is_child = false;
}

// send and recieve use unit seperators as end of transmission

int child_proc::send(const char *msg) {
  log(verbosity::DEBUG, "beginning send as %s\nwriting %s\n",
      is_child ? "child_write_fd" : "parent_write_fd", msg);
  write(parent_write_fd, msg, ft_strlen(msg));
  write(parent_write_fd, "\31", 1);
  log(verbosity::DEBUG, "finishing send\n");
  return ft_strlen(msg) + 1;
}

int child_proc::send(std::string msg) { return send(msg.c_str()); }

std::string child_proc::recieve() {
  char c;
  std::string ret;
  log(verbosity::DEBUG, "beginning recieve\nreading from fd %s\n",
      is_child ? "parent_read_fd" : "child_read_fd");
  while (read(child_read_fd, &c, 1)) {
    log(verbosity::DEBUG, "recieved char %i\n", c);
    if (c == '\31') {
      break;
    } else if (c == '\4') {
      exit(0);
    } else {
      ret.push_back(c);
    }
  }

  log(verbosity::DEBUG, "finishing recieve\n");
  return ret;
}

void child_proc::kill() {
  log(verbosity::DEBUG, "in kill\n");
  if (is_child)
    exit(0);
  else
    send("\4");
}

child_proc::~child_proc() {
  close(child_read_fd);
  close(child_write_fd);
  close(parent_read_fd);
  close(parent_write_fd);
}

}; // namespace libqm
