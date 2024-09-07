/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:54:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 21:33:34 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *str,char first_split, char last_split);
char	**ft_split(char const *s, char c);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
char *where_is(char *str);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
// char *read_file(int fd);
// int	write_file(char *to_write, int fd);
void error_fork(int fd1[2]);
void child_fork_fun(int fd1[2], char **str);
char *parent_fork_fun(int fd1[2], char **str);
char *my_pipe(char **str);

#endif