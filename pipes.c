/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/26 17:01:08 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	allocate_fds(int ***fd, pid_t **frs, int j)
{
	int	i;

	i = 0;
	*fd = malloc(sizeof(int *) * (j + 1));
	if (!*fd)
		exit(1);
	*frs = malloc(sizeof(pid_t) * j);
	if (!*frs)
	{
		free(*fd);
		exit(1);
	}
	while (i < j + 1)
	{
		fd[0][i] = malloc(sizeof(int) * (2));
		if (!fd[0][i])
		{
			while (--i >= 0)
				free(fd[0][i]);
			free(*fd);
			free(*frs);
			exit(1);
		}
		i++;
	}
}

void	child_execve(int **fd1, char **strs, pid_t *frs, t_info *info)
{
	if (info->is_for_w == 0)
		dup2(fd1[info->i_childs + 1][1], STDOUT_FILENO);
	else
		dup2(info->fd_file_w, STDOUT_FILENO);
	close(fd1[info->i_childs + 1][1]);
	if (info->is_for_w == 1)
		close(info->fd_file_w);
	execve(info->path_commd, strs, info->envp);
	perror("child_execve, execve");
	de_allocate(&fd1, &frs, info->str_i);
	free_split(strs, info->i_split);
	free_char(info->path_commd);
	exit(1);
}

void	childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	char	**strs;

	strs = ft_split(str[info->i_childs + info->offset], ' ', info);
	if (!strs)
		return (error_pipe(fd1, -3, info, NULL),
			de_allocate(&fd1, &frs, info->str_i), exit(1));
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd(
				ft_strjoin("zsh: command not found: ", strs[0], 0), 2, 2);
		return (error_pipe(fd1, -3, info, strs),
			de_allocate(&fd1, &frs, info->str_i),
			exit(127));
	}
	if (info->i_childs != 0)
		dup2(fd1[info->i_childs][0], STDIN_FILENO);
	close(fd1[info->i_childs][0]);
	if (info->i_childs == info->str_i - 1)
		info->is_for_w = 1;
	child_execve(fd1, strs, frs, info);
	exit(0);
}

void	init_childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (info->i_childs < info->str_i)
	{
		if (info->i_childs == info->str_i -1)
		{
			if (info->offset == 2)
				info->fd_file_w = open_file_w(str[info->ac - 1]);
			else
				info->fd_file_w = open_file_w_b(str[info->ac - 1]);
			if (info->fd_file_w == -1)
				break ;
		}
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fd1, info);
			childs(str, fd1, frs, info);
		}
		info->i_childs++;
	}
}

int	my_pipe(char **str, t_info *info)
{
	int		**fd1;
	pid_t	*frs;

	if (info->str_i <= 0)
		return (1);
	allocate_fds(&fd1, &frs, info->str_i);
	info->offset = init_files(str, info);
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
		if (pipe(fd1[info->i_fds++]) == -1)
			return (error_pipe(fd1, --info->i_fds, info, NULL),
				de_allocate(&fd1, &frs, info->str_i), exit(1), 1);
	init_childs(str, fd1, frs, info);
	return (finish_parent(&fd1, &frs, info));
}
