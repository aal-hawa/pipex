/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/15 18:32:21 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_pipe(int *fd1)
{
	perror("from pipe");
	close (fd1[0]);
	close (fd1[1]);
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

	if (str_i <=0)
		return ;
	fd_file_r = open_file_r(str[1]);
	fd_file_w = open_file_w(str[ac -1]);
	i = 0;
	while (i < str_i + 1)
		pipe(fd1[i++]);
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
			strs = ft_split(str[i + 2], ' ');
			if (!strs)
				return ;
			path_commd = get_from_env(env, strs[0]);
			if (!path_commd)
			{
				perror("path_commd");
				free(strs);
				close(fd1[i][0]);
				close(fd1[i][1]);
				exit (1);
			}
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
