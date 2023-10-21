/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiprocessing.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:04:30 by qmattor           #+#    #+#             */
/*   Updated: 2023/10/20 21:23:01 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.hpp"
#include "libft/libft.h"
#include <string>
#include <unistd.h>

struct child_proc {
  child_proc();
  int send(const char *msg);
  int send(std::string msg);
  std::string receive();
  template <typename F, class... Args> void start(F f, Args... args);

private:
  bool is_child;
  bool in_use;
  int parent_read_fd;
  int parent_write_fd;
  int child_read_fd;
  int child_write_fd;
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
  PIPE(&fd[2]);
  this->parent_read_fd = fd[0];
  this->parent_write_fd = fd[1];
  this->child_read_fd = fd[2];
  this->child_write_fd = fd[3];
  in_use = false;
  is_child = false;
}

template <typename F, class... Args> void child_proc::start(F f, Args... args) {
  if (in_use)
    QM_exception(std::runtime_error("Process is already in use"));
  in_use = true;
  FORK({
    is_child = true;
    f(args...);
  });
  is_child = false;
}

// send and recieve use unit seperators as end of transmission

int child_proc::send(const char *msg) {
  if (is_child) {
    write(child_write_fd, msg, ft_strlen(msg));
    write(child_write_fd, "\31", 1);
  } else {
    write(parent_write_fd, msg, ft_strlen(msg));
    write(parent_write_fd, "\31", 1);
  }
  return ft_strlen(msg) + 1;
}

int child_proc::send(std::string msg) {
  const char *mgs = ft_strdup(msg.c_str());
  return send(mgs);
}

std::string child_proc::receive() {
  char c;
  std::string ret;
  while (read(!is_child ? parent_read_fd : child_read_fd, &c, 1))
    if (c == '\31')
      break;
    else
      ret.push_back(c);
  return ret;
}
