/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:18:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/18 14:09:28 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_r(char *name_file)
{
	int	fd;
	fd = open(name_file, O_RDONLY, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
int	open_file_w(char *name_file)
{
	int	fd;
	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC,  0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
int	open_file_w_b(char *name_file)
{
	int	fd;
	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND,  0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_r_w(char *name_file)
{
	int	fd;
	fd = open(name_file, O_RDWR | O_CREAT | O_TRUNC,  0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
// char *read_file(int fd)
// {
// 	char *file;
	
// 	file = malloc(sizeof(char) * 10000);
// 	if(read(fd, file, 10000) == -1)
// 	{
// 		perror("from read_file, read");
// 		return (NULL);
// 	}
// 	return (file);
// }
// int	write_file(char *to_write, int fd)
// {
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	if (write(STDOUT_FILENO, to_write, sizeof(to_write)) == -1)
// 	{
// 		perror("from write_file, write");
// 		return (-1);
// 	}
// 	return (0);
// }