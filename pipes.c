/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/14 19:36:55 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_pipe(int *fd1)
{
	perror("from pipe");
	close (fd1[0]);
	close (fd1[1]);
}
int* frs_m(pid_t *frs, int str_i, int	*fd1)
{	
	int	i;

	i = 0;
	frs = malloc(sizeof(pid_t) * str_i);
	perror("aaaaaaaaaaaaa");

	while (i < str_i)
	{
		frs[i] = fork();
		if (frs[i] == -1)
		{
			perror("aaaaaaaaaaaaa");
			// error_fork_m(*frs, i);
			error_fork(fd1);
			return NULL;
		}
		i++;
	}
	return (frs);
}
void my_pipe(int ac, char **str, char *env)
{

	int	fd1[2];
	pid_t	frs;
	int	i;
	char **strs;
	char *path_commd;
	int	fd_file;
	int str_i;

	str_i = ac - 3;
	if (str_i <=0)
		return ;
	// frs = NULL;
	// frs = frs_m(frs, str_i, fd1);
	i = 0;
	while (i < str_i)
	{
		perror("b b b b ");
		pipe(fd1);
		frs = fork();
		perror("n n n n n");


		if (frs == 0)
		{
			fprintf(stderr, "i ch: %d\n", i);
			if (i == 0)
			{
				perror("yyyyyyyyyy");
				fd_file = open_file_r(str[1]);
				fprintf(stderr, "fd_file ch: %d\n", fd_file);
				fprintf(stderr, "str[ac -1] ch: %s\n", str[ac -1]);
				// fd_file == -1 make some thing ...
				perror("sssssssss");
				dup2(fd_file, STDIN_FILENO);
				close(fd_file);
			}
			strs = ft_split(str[i + 2], ' ');
			if (!strs)
				return ;
			path_commd = get_from_env(env, strs[0]);
			if (!path_commd)
			{
				perror("path_commd");
				free(strs);
				close(fd1[0]);
				close(fd1[1]);
				exit (1);
			}
			child_bonus(fd1, strs, path_commd);
		}
		else
		{
			// fprintf(stderr, "i pr: %d\n", i);

			perror("ooooooooooooo");

			dup2(fd1[0], STDIN_FILENO);
			if (i  == str_i - 1)
			{
				perror("gggggggggggg");
				fd_file = open_file_w(str[ac -1]);
				fprintf(stderr, "fd_file pr: %d\n", fd_file);
				fprintf(stderr, "str[ac -1] pr: %s\n", str[ac -1]);

				perror("hhhhhhhhhhh");
				dup2(fd_file, STDOUT_FILENO);
				close(fd_file);
			}
			close(fd1[0]);
			close(fd1[1]);
			// free(strs);
			// strs = NULL;
		}
		i++;
	}
	i = 0;
	// while (i < str_i)
	// 	waitpid(frs[i++], NULL, 0);
	// free(frs);
	// frs = NULL;
}
