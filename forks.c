/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:23:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 21:37:00 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_fork(int fd1[2])
{
	perror("from fork");
	close (fd1[0]);
	close (fd1[1]);
}

void child_fork_fun(int fd1[2], char **str)
{
	int	fd_file;
	char **strs;
	char *path_commd;
	
	strs = ft_split(str[2], ' ');
	if (!strs)
		return ;
	path_commd = where_is(strs[0]);
	if (!path_commd)
	{
		free(strs);
		return ;
	}
	fd_file = open_file_r(str[1]);
	if (fd_file == -1)
		return ;
	dup2(fd_file,STDIN_FILENO);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[0]);
	// close(fd1[1]);
	execve(path_commd, strs, NULL);
	perror("child_fork_fun, execve");
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
char *parent_fork_fun(int fd1[2], char **str)
{
	int	fd_file;
	char **strs;
	char *path_commd;
	
	strs = ft_split(str[2], ' ');
	if (!strs)
		return (NULL);
	path_commd = where_is(strs[0]);
	if (!path_commd)
	{
		free(strs);
		return (NULL);
	}
	fd_file = open_file_w(str[4]);
	if (fd_file == -1)
	{
		perror("from open file");
		return (NULL);
	}
	dup2(fd_file, STDOUT_FILENO);
	dup2(fd1[0], STDIN_FILENO);
	// wait(NULL);
	execve(path_commd, strs, NULL);
	perror("parent_fork_fun, execve");
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