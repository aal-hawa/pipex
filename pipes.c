/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/18 18:23:00 by aal-hawa         ###   ########.fr       */
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
int	init_files(int ac, char **str, int fd_file_r, int fd_file_w)
{
	int	offset;

	offset = 2;
	if (ft_strncmp(str[1], "here_doc", 8) == 0)
	{
		fd_file_r = open_file_r_w("tmp");
		if (fd_file_r == -1)
			return (3);
		ft_putstr_fd(get_next_line(0), fd_file_r);
		offset = 3;
		fd_file_w = open_file_w_b(str[ac -1]);
		if (fd_file_w == -1)
			return (error_pipe(NULL, -1, fd_file_r, -2, NULL), 3);
	}
	else
	{
		fd_file_r = open_file_r(str[1]);
		if (fd_file_r == -1)
			return (2);
		fd_file_w = open_file_w(str[ac -1]);
		if (fd_file_w == -1)
			return (error_pipe(NULL, -1, fd_file_r, -2, NULL), 2);
	}
	return (offset);
}

void my_pipe(int ac, char **str, char *env, int str_i)
{
	int	fd1[str_i + 1][2];
	pid_t	frs[str_i];
	int	i;
	char **strs;
	char *path_commd;
	int	fd_file_r;
	int	fd_file_w;
	// char *here_doc;
	int offset = 2;

	if (str_i <=0)
		return ;
	if (ft_strncmp(str[1], "here_doc", 8) == 0)
	{
		// here_doc = get_next_line(0);
		fd_file_r = open_file_r_w("tmp");
		if (fd_file_r == -1)
			return ;
		ft_putstr_fd(get_next_line(0), fd_file_r);
		offset = 3;
		fd_file_w = open_file_w_b(str[ac -1]);
		if (fd_file_w == -1)
			return (error_pipe(fd1, -1, fd_file_r, -2, NULL));
	}
	else
	{
		fd_file_r = open_file_r(str[1]);
		if (fd_file_r == -1)
			return ;
		fd_file_w = open_file_w(str[ac -1]);
		if (fd_file_w == -1)
			return (error_pipe(fd1, -1, fd_file_r, -2, NULL));
	}
	i = 0;
	while (i < str_i + 1)
	{
		if (pipe(fd1[i++]) == -1)
			return (error_pipe(fd1, i--, fd_file_r, fd_file_w, NULL));
	}
	i = 0;
	while (i < str_i)
	{
		frs[i] = fork();
		if (frs[i] == 0)
		{
			fprintf(stderr, "i ch: %d\n", i);
			int j = 0;
			while(j < str_i + 1)
			{
				if(i != j)
					close(fd1[j][0]);
				if(i + 1 != j)
					close(fd1[j][1]);
				j++;
			}
			if (i == 0)
			{
				dup2(fd_file_r, STDIN_FILENO);
				close(fd_file_r); 
			}
			strs = ft_split(str[i + offset], ' ');
			if (!strs)
				return (error_pipe(fd1, i--, fd_file_r, fd_file_w, NULL));
			path_commd = get_from_env(env, strs[0]);
			if (!path_commd)
				return (error_pipe(fd1, i--, fd_file_r, fd_file_w, strs));
			dup2(fd1[i][0], STDIN_FILENO);
			close(fd1[i][0]);
			if (i != str_i -1)
				child_bonus(fd1[i + 1][1], strs, path_commd);
			else
			{
				child_bonus(fd_file_w, strs, path_commd);
				close(fd1[i + 1][1]);
			}
			exit(0);
		}
		i++;
	}
	i = 0;
	while(i < str_i + 1)
	{
		close(fd1[i][0]);
		close(fd1[i][1]);
		i++;
	}
	i = 0;
	while (i < str_i)
	{
		wait(NULL);
		i++;
	}
	// free(frs);
	// frs = NULL;
}
