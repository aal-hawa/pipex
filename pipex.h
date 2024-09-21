/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:54:56 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/21 15:50:56 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
// #include "get_next_line.h"

typedef struct	s_info
{
	int		i_fds;
	int		i_childs;
	int		i_wait;
	int		fd_file_r;
	int		fd_file_w;
	int		offset;
	int		ac;
	int		str_i;
	char	*env;
	char	*limiter;
	int		i_limiter;
	char	*path_commd;
	char	**envp;
	int		is_for_w;
	int		is_bonus;
}	t_info;

size_t	ft_strlen(const char *s);
char	*ft_strdup(char *str,char first_split, char last_split);
char	**ft_split(char const *s, char c);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
int	open_file_r(char *name_file);
int	open_file_w(char *name_file);
void my_pipe(char **str, t_info *info);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2, int is_path);
char *get_from_env(char *env, char *str);
int	open_file_r_w(char *name_file);
int	open_file_w_b(char *name_file);
void	env_data(char **envp, char **env);
int	init_files(char **str, t_info *info);
void wait_fun(t_info *info);
void	close_fds_parent(int **fd1, t_info *info);
void	close_fds_childs(int **fd1, t_info *info);
void error_pipe(int **fd1, int i, t_info *info, char **strs);
char	*get_next_line(t_info *info);
char	*ft_strjoin_g(char *s1, char *s2, int *is_done, t_info *info);
char	*free_char(char *this_string);
void	ft_putstr_fd(char *s, int fd, int is_malloc);

#endif