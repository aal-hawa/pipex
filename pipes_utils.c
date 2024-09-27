/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:32:30 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/27 18:09:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splits(char **strs)
{
	int	i;

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

void	error_pipe(int **fd1, int i, t_info *info, char **strs)
{
	if (i == -3)
	{
		close(fd1[info->i_childs][0]);
		close(fd1[info->i_childs + 1][1]);
	}
	while (i >= 0)
	{
		close(fd1[i][0]);
		close(fd1[i][1]);
		i--;
	}
	if (info->fd_file_r >= 0)
		close(info->fd_file_r);
	if (info->fd_file_w >= 0)
		close(info->fd_file_w);
	if (strs)
		free_splits(strs);
	if (info->path_commd)
		free_char(info->path_commd);
}

void	de_allocate(int ***fd, pid_t **frs, int i)
{
	while (i >= 0)
	{
		while (i >= 0)
			free(fd[0][i--]);
		free(*fd);
		free(*frs);
		*fd = NULL;
		*frs = NULL;
	}
}

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
