/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:23:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/08 19:23:04 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_fork(int fd1[2])
{
	perror("from fork");
	close (fd1[0]);
	close (fd1[1]);
}

void child_fork_fun(int *fd1, char **str, char *env)
{
	int	fd_file;
	char **strs;
	char *path_commd;
	
	strs = ft_split(str[2], ' ');
	if (!strs)
	{
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	// path_commd = where_is(strs[0]);
	path_commd = get_from_env(env, strs[0]);
	// printf("path_commd: %s\n", path_commd);
	// write(1, "path_commd: ", 12);
	// int i = 0;
	// while (path_commd[i])
	// {
	// 	write(1, &path_commd[i], 1);
	// 	i++;
	// }
	// write(1, &path_commd, sizeof(path_commd));
	// write(1, "\n", 1);
	if (!path_commd)
	{
		// printf("aaaaaaaaaaaaaa");
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	fd_file = open_file_r(str[1]);
	if (fd_file == -1)
	{
		perror("child_fork_fun, execve");
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	dup2(fd_file, STDIN_FILENO);
	// close(fd_file);
	close(fd1[0]);
	dup2(fd1[1], STDOUT_FILENO);
	// printf("path_commd: %s\n",(path_commd));
	execve(path_commd, strs, NULL);
	// execvp(strs[0], strs);
	perror("child_fork_fun, execve");
	close(fd1[0]);
	close(fd1[1]);
}

// void child_fork_fun(int fd1[2], int fd2[2], char *path_commd, char **strs)
// {
// 	close(fd2[0]);
// 	close(fd1[1]);
// 	dup2(fd1[0], STDIN_FILENO);
// 	dup2(fd2[1], STDOUT_FILENO);
// 	close(fd1[0]);
// 	close(fd2[1]);
// 	execve(path_commd, strs, NULL);
// 	perror("before pibe, execve");
// }

void	child_second(int *fd1, char **str, char **strs, char *path_commd)
{
	int	fd_file;
	
	fd_file = open_file_w(str[4]);
	if (fd_file == -1)
	{
		perror("from open file");
		close(fd1[0]);
		close(fd1[1]);
		return ;
	}
	dup2(fd_file, STDOUT_FILENO);
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[1]);
	close(fd1[0]);
	// wait(NULL);
	// printf("path_commd: %s\n",(path_commd));
	execve(path_commd, strs, NULL);
	// execvp(strs[0], strs);
	perror("child_second, execve");
	close(fd1[0]);
	close(fd1[1]);
}
char *parent_fork_fun(int *fd1, char **str, char *env)
{
	// int	fd_file;
	char **strs;
	char *path_commd;
	pid_t	fr;
	
	
	strs = ft_split(str[3], ' ');
	if (!strs)
		return (NULL);
	// path_commd = where_is(strs[0]);
	path_commd = get_from_env(env, strs[0]);
	// printf("path_commd: %s", path_commd);
	if (!path_commd)
	{
		free(strs);
		close(fd1[0]);
		close(fd1[1]);
		return (NULL);
	}
	fr = fork();
	if (fr == -1)
	{
		error_fork(fd1);
		return (NULL);
	}
	if (fr == 0)
	{
		child_second(fd1, str, strs, path_commd);
		return NULL;
	}
	// fd_file = open_file_w(str[4]);
	// if (fd_file == -1)
	// {
	// 	perror("from open file");
	// 	return (NULL);
	// }
	// dup2(fd_file, STDOUT_FILENO);
	// dup2(fd1[0], STDIN_FILENO);
	// // close(fd1[0]);
	// close(fd1[1]);
	close(fd1[0]);
	close(fd1[1]);
	wait(NULL);
	// execve(path_commd, strs, NULL);
	// perror("parent_fork_fun, execve");
	return (NULL);
}
// char *parent_fork_fun(int fd1[2], int fd2[2], char *res)
// {
// 	char *out_text;
// 	// fd2[0]  fd1[1]
// 	close(fd1[0]);
// 	close(fd2[1]);
// 	if(write_file(res, fd1[1])== -1)
// 	{
// 		close(fd1[1]);
// 		close(fd2[0]);
// 		perror("parent_fork_fun, write_file");
// 		wait(NULL);
// 		return (NULL);
// 	}
// 	close(fd1[1]);
// 	out_text = read_file(fd2[0]);
// 	close(fd2[0]);
// 	wait(NULL);
// 	return (out_text);
// }