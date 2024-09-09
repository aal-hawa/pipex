/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/09 18:47:48 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_pipe(int *fd1)
{
	perror("from pipe");
	close (fd1[0]);
	close (fd1[1]);
}

// int	init_fds(int *fd1)
// {
// 	if (pipe(fd1) == -1)
// 	{
// 		perror("from pipe");
// 		return (1);
// 	}
// 	return (0);
// }

void my_pipe(int ac, char **str, char *env)
{
	int	fd1[2];
	pid_t	fr;
	
	if (pipe(fd1) == -1)
	{
		perror("from pipe");
		return ;
	}
	fr = fork();
	if (fr == -1)
		return (error_fork(fd1));
	if (fr == 0)
	{
		child_fork_fun(fd1, str, env);
		return ;
	}
	// wait(NULL);
	parent_fork_fun(ac, fd1, str, env);
	return ;
}
