/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:30 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/24 18:11:32 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_splits(char **strs)
{
	int i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			strs[i] = free_char(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

int	wait_fun(t_info *info)
{
	int	exit_child;
	int	is_error_127;

	info->i_wait = 0;
	is_error_127 = 0;
	while (info->i_wait < info->str_i)
	{
		wait(&exit_child);
		if (exit_child == 127 || exit_child == 256 )
			is_error_127 = 1;
		info->i_wait++;
	}
	return (is_error_127);
}

void error_pipe(int **fd1, int i, t_info *info, char **strs)
{
	if (i == -3)
	{
		close(fd1[info->i_childs][0]);
		close(fd1[info->i_childs + 1][1]);
	}
	while (i >= 0)
	{
		close (fd1[i][0]);
		close (fd1[i][1]);
		i--;
	}
	if (info->fd_file_r >= 0)
		close (info->fd_file_r);
	if (info->fd_file_w >= 0)
		close (info->fd_file_w);
	if (strs)
		free_splits(strs);
	if (info->path_commd)
		free_char (info->path_commd);
}

void	close_fds_childs(int **fd1, t_info *info)
{
	int j;

	j = 0;
	while(j < info->str_i + 1)
	{
		if(info->i_childs != j)
			close(fd1[j][0]);
		if(info->i_childs + 1 != j)
			close(fd1[j][1]);
		j++;
	}
	if (info->i_childs == 0 && info->fd_file_r != -1)
		dup2(info->fd_file_r, STDIN_FILENO);
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
}

void	close_fds_parent(int **fd1, t_info *info)
{
	int	i;

	i = 0;
	while(i < info->str_i + 1)
	{
		close(fd1[i][0]);
		close(fd1[i][1]);
		i++;
	}
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
	if (info->fd_file_w != -1)
		close(info->fd_file_w);
	if (info->limiter != NULL)
		free_char(info->limiter);
	
}
int	finish_parent(int ***fd, pid_t **frs, t_info *info)
{
	int	is_error_127;
	
	close_fds_parent(*fd, info);
	is_error_127 = wait_fun(info);
	de_allocate(fd, frs, info->str_i);
	return (is_error_127);
}