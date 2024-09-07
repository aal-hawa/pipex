/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 21:34:33 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_pipe(int fd1[2])
{
	perror("from pipe");
	close (fd1[0]);
	close (fd1[1]);
}

int	init_fds(int fd1[2])
{
	if (pipe(fd1) == -1)
	{
		perror("from pipe");
		return (1);
	}
	return (0);
}

char *my_pipe(char **str)
{
	int	fd1[2];
	pid_t	fr;
	
	if (init_fds(fd1) == -1)
		return(error_pipe(fd1), NULL);
	fr = fork();
	if (fr == -1)
		return (error_fork(fd1), NULL);
	if (fr == 0)
	{
		child_fork_fun(fd1, str);
		return (NULL);
	}
	parent_fork_fun(fd1, str);
	return (NULL);
}

// char *my_pipe(char *str, char *res)
// {
// 	char **strs;
// 	char *path_commd;
// 	int	fd1[2];
// 	int	fd2[2];
// 	int	fr;
// 	char *out_text;
	
// 	strs = ft_split(str, ' ');
// 	if (!strs)
// 		return (NULL);
// 	path_commd = where_is(strs[0]);
// 	if (!path_commd)
// 	{
// 		free(strs);
// 		return (NULL);
// 	}
// 	if (init_fds(fd1, fd2) == -1)
// 		return(error_pipe(fd1), NULL);
// 	fr = fork();
// 	if (fr == -1)
// 		return (error_fork(fd1, fd2), NULL);
// 	if (fr == 0)
// 	{
// 		child_fork_fun(fd1, fd2, path_commd, strs);
// 		return (NULL);
// 	}
// 	out_text = parent_fork_fun(fd1, fd2, res);
// 	free(strs);
// 	return (out_text);
// }
