/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/19 19:14:01 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_pipe(int fd1[][2], int i, int file_1, int file_2, char **strs)
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
	if (file_1 >= 0)
	{
		close (file_1);
	}
	if (file_2 >= 0)
	{
		close (file_2);
	}
	if (!strs)
	{
		free(strs);
		strs = NULL;
	}
}
int	init_files(char **str, info_t *info)
{
	info->offset = 2;
	if (ft_strncmp(str[1], "here_doc", 8) == 0)
	{
		info->fd_file_r = open_file_r_w("tmp");
		if (info->fd_file_r == -1)
			return (3);
		ft_putstr_fd(get_next_line(0), info->fd_file_r);
		info->offset = 3;
		info->fd_file_w = open_file_w_b(str[info->ac -1]);
		if (info->fd_file_w == -1)
			return (error_pipe(NULL, -1, info->fd_file_r, -2, NULL), 3);
	}
	else
	{
		info->fd_file_r = open_file_r(str[1]);
		if (info->fd_file_r == -1)
			return (2);
		info->fd_file_w = open_file_w(str[info->ac -1]);
		if (info->fd_file_w == -1)
			return (error_pipe(NULL, -1, info->fd_file_r, -2, NULL), 2);
	}
	return (info->offset);
}
void wait_fun(info_t *info)
{
	info->i_wait = 0;
	while (info->i_wait < info->str_i)
	{
		wait(NULL);
		info->i_wait++;
	}
}
void	close_fds_parent(int fd1[][2], info_t *info)
{
	info->i_childs = 0;
	while(info->i_childs < info->str_i + 1)
	{
		close(fd1[info->i_childs][0]);
		close(fd1[info->i_childs][1]);
		info->i_childs++;
	}
}
void	close_fds_childs(int fd1[][2], info_t *info)
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

void	childs(char **str, int fd1[][2], info_t *info)
{
	char **strs;
	char *path_commd;
	
	strs = ft_split(str[info->i_childs + info->offset], ' ');
	if (!strs)
		return (error_pipe(fd1, info->i_childs--, info->fd_file_r, info->fd_file_w, NULL));
	path_commd = get_from_env(info->env, strs[0]);
	if (!path_commd)
		return (error_pipe(fd1, info->i_childs--, info->fd_file_r, info->fd_file_w, strs));
	dup2(fd1[info->i_childs][0], STDIN_FILENO);
	close(fd1[info->i_childs][0]);
	if (info->i_childs != info->str_i -1)
		child_bonus(fd1[info->i_childs + 1][1], strs, path_commd);
	else
	{
		child_bonus(info->fd_file_w, strs, path_commd);
		close(fd1[info->i_childs + 1][1]);
	}
	exit(0);
}

void my_pipe(char **str, info_t *info)
{
	int	fd1[info->str_i + 1][2];
	pid_t	frs[info->str_i];

	if (info->str_i <=0)
		return ;
	info->offset  = init_files(str, info);
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
		if (pipe(fd1[info->i_fds++]) == -1)
			return (error_pipe(fd1, info->i_fds--, info->fd_file_r, info->fd_file_w, NULL));
	info->i_childs = 0;
	while (info->i_childs < info->str_i)
	{
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			fprintf(stderr, "i ch: %d\n", info->i_childs);
			close_fds_childs(fd1, info);
			childs(str, fd1, info);
		}
		info->i_childs++;
	}
	close_fds_parent(fd1, info);
	wait_fun(info);
}
