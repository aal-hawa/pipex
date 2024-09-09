/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:23:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/09 20:53:21 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_fork(int *fd1)
{
	perror("from fork");
	close (fd1[0]);
	close (fd1[1]);
}
void	here_doc(int *fd1, char **str, char *env)
{
	char **strs;
	char *path_commd;
	
	// str[3] = ft_strjoin(str[3], " << LIMITER", 0);
	strs = ft_split(str[3], ' ');
	if (!strs)
	{
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	path_commd = get_from_env(env, strs[0]);
	if (!path_commd)
	{
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	// int i = 0;
	// while (strs[i])
	// {
	// 	printf("%s\n", strs[i]);
	// 	i++;
	// }
	// return;
	dup2(fd1[1], STDOUT_FILENO);
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[1]);
	close(fd1[0]);
	execve(path_commd, strs, NULL);
	perror("child_fork_fun, execve");
}

void	child_fork_fun(int *fd1, char **str, char *env)
{
	int	fd_file;
	char **strs;
	char *path_commd;
	
	if (ft_strncmp(str[1] , "here_doc", 8) == 0)
	{
		here_doc(fd1, str, env);
		return ;
	}
	fd_file = open_file_r(str[1]);
	if (fd_file == -1)
	{
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	strs = ft_split(str[2], ' ');
	if (!strs)
	{
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	path_commd = get_from_env(env, strs[0]);
	if (!path_commd)
	{
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	close(fd1[0]);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[1]);
	execve(path_commd, strs, NULL);
	perror("child_fork_fun, execve");
}
void	child_bonus(int *fd1, char **strs, char *path_commd)
{
	dup2(fd1[0], STDIN_FILENO);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[0]);
	close(fd1[1]);
	execve(path_commd, strs, NULL);
}
void	child_second(int *fd1, int fd_file, char **strs, char *path_commd)
{
	// int	fd_file;

	// fd_file = open_file_w(str[4]);
	// if (fd_file == -1)
	// {
	// 	close(fd1[0]);
	// 	close(fd1[1]);
	// 	return ;
	// }
	dup2(fd_file, STDOUT_FILENO);
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[1]);
	close(fd1[0]);
	execve(path_commd, strs, NULL);
}
void	cmnds_between(int *fd1, char **str, char *env, int str_i)
{
	if (!str[str_i] || !str[str_i + 1] || !str[str_i + 2] || !str[str_i + 3])
		return ;
	char **strs;
	char *path_commd;
	pid_t	fr;
	
	strs = ft_split(str[str_i], ' ');
	if (!strs)
		return ;
	
	path_commd = get_from_env(env, strs[0]);
	if (!path_commd)
	{
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	fr = fork();
	if (fr == -1)
	{
		error_fork(fd1);
		return ;
	}
	if (fr == 0)
	{
		child_bonus(fd1, strs, path_commd);
		return ;
	}
	// wait(NULL);
	cmnds_between(fd1, str, env, str_i + 1);
	close(fd1[0]);
	close(fd1[1]);
}
int	make_file(char **str)
{
	int	fd_file;

	fd_file = open_file_w(str[4]);
	return (fd_file);
	// if (fd_file == -1)
	// {
	// 	close(fd1[0]);
	// 	close(fd1[1]);
	// 	return ;
	// }
}
void	parent_fork_fun(int ac, int *fd1, char **str, char *env)
{
	char **strs;
	char *path_commd;
	pid_t	fr;
	int	fd_file;
	int i;

	if (ft_strncmp(str[1] , "here_doc", 8) == 0)
	{
		while (1)
		{
			// get next line
			char *line = get_next_line(0);
			if (ft_strncmp(line , "LIMITER\n", 8) == 0)
			{
				// close(fd1[0]);
				// close(fd1[1]);
				break ;
			}
		}
		
	}
	else
		cmnds_between(fd1, str, env, 3);
	
	fd_file = open_file_w(str[ac - 1]);
	strs = ft_split(str[ac - 2], ' ');
	if (!strs)
		return ;
	path_commd = get_from_env(env, strs[0]);
	if (!path_commd)
	{
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	fr = fork();
	if (fr == -1)
	{
		error_fork(fd1);
		return ;
	}
	if (fr == 0)
	{
		child_second(fd1, fd_file, strs, path_commd);
		return ;
	}
	close(fd1[0]);
	close(fd1[1]);
	i = ac - 3;
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
}
