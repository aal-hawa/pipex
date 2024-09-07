/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:18:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 21:00:03 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_r(char *name_file)
{
	int	fd;
	fd = open(name_file, O_RDONLY);
	if (fd == -1)
	{
		perror("open_file_r");
		// exit(1);
	}
	return (fd);
}
int	open_file_w(char *name_file)
{
	int	fd;
	fd = open(name_file, O_WRONLY);
	if (fd == -1)
	{
		perror("open_file_r");
		// exit(1);
	}
	// dup2(fd, STDOUT_FILENO);
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