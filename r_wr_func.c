/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:18:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 19:44:49 by aal-hawa         ###   ########.fr       */
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

int	init_files(char **str, t_info *info)
{
	info->offset = 2;
	if (ft_strncmp(str[1], "here_doc", 8) == 0)
	{
		info->fd_file_r = open_file_r_w("tmp");
		if (info->fd_file_r == -1)
			return (3);
		info->limiter =ft_strjoin(str[2], "\n", 0);
		info->i_limiter = ft_strlen (info->limiter);
		ft_putstr_fd(get_next_line(info), info->fd_file_r);
		info->offset = 3;
		info->fd_file_w = open_file_w_b(str[info->ac -1]);
		if (info->fd_file_w == -1)
			return (error_pipe(NULL, -1, info, NULL), 3);
	}
	else
	{
		info->fd_file_r = open_file_r(str[1]);
		if (info->fd_file_r == -1)
			return (2);
		info->fd_file_w = open_file_w(str[info->ac -1]);
		if (info->fd_file_w == -1)
			return (error_pipe(NULL, -1, info, NULL), 2);
	}
	return (info->offset);
}
