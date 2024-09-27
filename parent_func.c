/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:57:34 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/27 18:00:58 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_fun(t_info *info)
{
	int	exit_child;
	int	is_error_127;

	info->i_wait = 0;
	is_error_127 = 0;
	while (info->i_wait < info->str_i)
	{
		wait(&exit_child);
		if (exit_child % 255 == 127)
			is_error_127 = 1;
		info->i_wait++;
	}
	return (is_error_127);
}

void	close_fds_parent(int **fd1, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->str_i + 1)
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
