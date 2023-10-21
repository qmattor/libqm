/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmattor <Quincy_Mattor@student.uml.edu>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 09:59:08 by bopok             #+#    #+#             */
/*   Updated: 2023/10/20 20:49:23 by qmattor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

extern "C" {
#include "../libft/libft.h"
};
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 24
#define NOFLAG 0
#define ENDFILE 1
#define EOL 2

typedef struct s_file {
  char *buf;
  int index;
  char res;
  char flag;
  int fd;
} t_file;

t_file *newele(int fd);
void delele(t_file *thing);
int get_next_line(const int fd, char **line);
char *read_to_newline(t_file *file, char delimieter);
int get_next_line(const int fd, char **line, char delimieter);
#endif
