/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:34:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/25 20:36:31 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_info_main_b(int ac, char *env, char **envp, t_info *info)
{
	info->ac = ac;
	info->env = env;
	info->str_i = ac - 3;
	info->envp = envp;
	info->is_bonus = 1;
	info->limiter = NULL;
	info->i_split = 0;
	info->path_commd = NULL;
	info->env_null = 0;
}

int	main(int ac, char **arg, char **envp)
{
	char	*env;
	t_info	info;
	int		is_error_127;

	env_data(envp, &env);
	if (ac < 5)
		return (ft_putstr_fd("Pad argc\n", 2, 0), 0);
	init_info_main_b(ac, env, envp, &info);
	// info.dup_stdin = dup(STDIN_FILENO);
	// info.dup_stout = dup(STDIN_FILENO);
	if (!env)
		info.env_null = 1;
	if (ft_strncmp(arg[1], "here_doc", 8) != 0)
		is_error_127 = my_pipe(arg, &info);
	else
	{
		if (ac != 6)
			return (ft_putstr_fd("Pad argc\n", 2, 0), 0);
		info.str_i = ac - 4;
		is_error_127 = my_pipe(arg, &info);
	}
	if (ft_strncmp(arg[1], "here_doc", 8) == 0 && info.fd_file_w != -1)
		unlink ("/tmp/tmp_pipe");
	if (is_error_127 == 1)
		(close_fds(&info)), exit(127);
	close_fds(&info);
	return (0);
}
