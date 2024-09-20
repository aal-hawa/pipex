/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 20:49:25 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_execve(int fd1, char **strs, char *path_commd)
{
	dup2(fd1, STDOUT_FILENO);
	close(fd1);
	execve(path_commd, strs, NULL);
	perror("child_bonus, execve");
	free(strs);
	strs = NULL;
	exit (1);
}

void	childs(char **str, int **fd1, t_info *info)
{
	char **strs;
	char *path_commd;
	
	strs = ft_split(str[info->i_childs + info->offset], ' ');
	if (!strs)
		return (error_pipe(fd1, info->i_childs--, info, NULL));
	path_commd = get_from_env(info->env, strs[0]);
	if (!path_commd)
		return (error_pipe(fd1, info->i_childs--, info, strs));
	dup2(fd1[info->i_childs][0], STDIN_FILENO);
	close(fd1[info->i_childs][0]);
	if (info->i_childs != info->str_i -1)
		child_execve(fd1[info->i_childs + 1][1], strs, path_commd);
	else
	{
		child_execve(info->fd_file_w, strs, path_commd);
		close(fd1[info->i_childs + 1][1]);
	}
	exit(0);
}

void	allocate_fds(int ***fd, pid_t **frs, int j)
{
	int i;

	i = 0;
	*fd = malloc(sizeof(int) * (j + 1));
	if (!*fd)
		exit(1);
	*frs = malloc(sizeof(pid_t) * j);
	if (!*frs)
	{
		free(*fd);
		exit(1);
	}
	while (i < j  + 1)
	{
		fd[0][i] = malloc(sizeof(int) * (2));
		if (!fd[0][i])
		{
			while(--i >= 0)
				free(fd[0][i]);
			free(*fd);
			free(*frs);
			exit(1);
		}
		i++;
	}
}

void	de_allocate(int ***fd, pid_t **frs, int i)
{
	while (i >= 0)
	{
		while(i >= 0)
			free(fd[0][i--]);
		free(*fd);
		free(*frs);
		*fd = NULL;
		*frs = NULL;
		exit(1);
	}
}

void my_pipe(char **str, t_info *info)
{
	int		**fd1;
	pid_t	*frs;

	if (info->str_i <=0)
		return ;
	allocate_fds(&fd1, &frs, info->str_i);
	info->offset = init_files(str, info);
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
		if (pipe(fd1[info->i_fds++]) == -1)
			return (error_pipe(fd1, info->i_fds--, info, NULL));
	info->i_childs = 0;
	while (info->i_childs < info->str_i)
	{
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fd1, info);
			childs(str, fd1, info);
		}
		info->i_childs++;
	}
	close_fds_parent(fd1, info);
	wait_fun(info);
	de_allocate(&fd1, &frs, info->str_i  + 1);
}
