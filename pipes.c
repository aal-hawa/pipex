/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:55 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/29 11:33:15 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds_childs(int **fd1, t_info *info)
{
	int	j;

	j = 0;
	while (j < info->str_i + 1)
	{
		if (info->i_childs != j)
			close(fd1[j][0]);
		if (info->i_childs + 1 != j)
			close(fd1[j][1]);
		j++;
	}
	if (info->i_childs == 0 && info->fd_file_r != -1)
		dup2(info->fd_file_r, STDIN_FILENO);
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
}

void	child_execve(int **fd1, char **strs, pid_t *frs, t_info *info)
{
	if (info->is_for_w == 0)
		dup2(fd1[info->i_childs + 1][1], STDOUT_FILENO);
	else
		dup2(info->fd_file_w, STDOUT_FILENO);
	close(fd1[info->i_childs + 1][1]);
	if (info->is_for_w == 1)
		close(info->fd_file_w);
	execve(info->path_commd, strs, info->envp);
	perror(info->path_commd);
	de_allocate(&fd1, &frs, info->str_i);
	free_split(strs, info->i_split);
	free_char(info->path_commd);
	exit(1);
}

void	childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	char	**strs;

	strs = ft_split(str[info->i_childs + info->offset], ' ', info);
	if (!strs)
		return (error_pipe(fd1, -3, info, NULL),
			de_allocate(&fd1, &frs, info->str_i), exit(1));
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd(
				ft_strjoin("zsh: command not found: ", strs[0], 0), 2, 2);
		return (error_pipe(fd1, -3, info, strs),
			de_allocate(&fd1, &frs, info->str_i),
			exit(127));
	}
	if (info->i_childs != 0)
		dup2(fd1[info->i_childs][0], STDIN_FILENO);
	close(fd1[info->i_childs][0]);
	if (info->i_childs == info->str_i - 1)
		info->is_for_w = 1;
	child_execve(fd1, strs, frs, info);
	exit(0);
}

void	init_childs(char **str, int **fd1, pid_t *frs, t_info *info)
{
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (info->i_childs < info->str_i)
	{
		if (info->i_childs == info->str_i -1)
		{
			if (info->offset == 2)
				info->fd_file_w = open_file_w(str[info->ac - 1]);
			else
				info->fd_file_w = open_file_w_b(str[info->ac - 1]);
			if (info->fd_file_w == -1)
			{
				info->is_exit_one = 1;
				break ;
			}
		}
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fd1, info);
			childs(str, fd1, frs, info);
		}
		info->i_childs++;
	}
}

int	my_pipe(char **str, t_info *info)
{
	int		**fd1;
	pid_t	*frs;

	if (info->str_i <= 0)
		return (1);
	allocate_fds(&fd1, &frs, info->str_i);
	info->offset = init_files(str, info);
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
		if (pipe(fd1[info->i_fds++]) == -1)
			return (error_pipe(fd1, --info->i_fds, info, NULL),
				de_allocate(&fd1, &frs, info->str_i), exit(1), 1);
	init_childs(str, fd1, frs, info);
	return (finish_parent(&fd1, &frs, info));
}
