/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:30 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 20:44:33 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void wait_fun(t_info *info)
{
	info->i_wait = 0;
	while (info->i_wait < info->str_i)
	{
		wait(NULL);
		info->i_wait++;
	}
}

void error_pipe(int **fd1, int i, t_info *info, char **strs)
{
	perror("from pipe");
	if (i >=0)
	{
		while (i >= 0)
		{
			close (fd1[i][0]);
			close (fd1[i][1]);
			i--;
		}
	}
	if (info->fd_file_r >= 0)
	{
		close (info->fd_file_r);
	}
	if (info->fd_file_w >= 0)
	{
		close (info->fd_file_w);
	}
	if (!strs)
	{
		free(strs);
		strs = NULL;
	}
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
	if (info->i_childs == 0)
	{
		dup2(info->fd_file_r, STDIN_FILENO);
		close(info->fd_file_r); 
	}
}

void	close_fds_parent(int **fd1, t_info *info)
{
	info->i_childs = 0;
	while(info->i_childs < info->str_i + 1)
	{
		close(fd1[info->i_childs][0]);
		close(fd1[info->i_childs][1]);
		info->i_childs++;
	}
}
