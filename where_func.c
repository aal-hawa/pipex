/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:24:47 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 19:25:11 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *where_is(char *str)
{
	char *path;
	int	fd[2];
	int	fr;
	char *where_is_arry[3];
	
	path = malloc(sizeof(char) * 10000);
	where_is_arry[0] ="whereis";
	where_is_arry[1] =str;
	where_is_arry[2] = NULL;
	if (pipe(fd) == -1)
	{
		perror("from where_is, pibe");
		return (NULL);
	}
	fr = fork();
	if (fr == -1)
	{
		perror("from where_is, fork");
		close (fd[0]);
		close (fd[1]);
		return (NULL);
	}
	if (fr == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/bin/whereis", where_is_arry, NULL);
	}
	if(read (fd[0], path, 10000) == -1)
	{
		perror("from where_is, read");
		close(fd[0]);
		close(fd[1]);
		return (NULL);
	}
	path = ft_strdup(path, '/', ' ');
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	return (path);
}