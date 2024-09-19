/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:54:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/19 19:01:22 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "get_next_line.h"

typedef struct	info_l
{
	int	i_fds;
	int	i_childs;
	int	i_wait;
	int	fd_file_r;
	int	fd_file_w;
	int offset;
	int ac;
	int str_i;
	char *env;
}	info_t;

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *str,char first_split, char last_split);
char	**ft_split(char const *s, char c);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
char *where_is(char *str);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
void error_fork(int *fd1);
void child_fork_fun(int *fd1, char **str, char *env);
void parent_fork_fun(int ac, int *fd1, char **str, char *env);
void my_pipe(char **str, info_t *info);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2, int is_path);
char *get_from_env(char *env, char *str);
void	child_bonus(int fd1, char **strs, char *path_commd);
void	ft_putstr_fd(char *s, int fd);
int	open_file_r_w(char *name_file);
int	open_file_w_b(char *name_file);

#endif