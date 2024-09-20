/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:34:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 19:38:14 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init_info_main_b(int ac, char *env, t_info *info)
{
	info->ac = ac;
	info->env = env;
	info->str_i = ac - 3;
}

int	main(int ac, char **arg, char **envp)
{
	char *env;
	t_info info;

	env_data(envp, &env);
	if (ac < 5)
		return (ft_putstr_fd("Pad argc\n", 2), 0);
	init_info_main_b(ac, env, &info);
	if (ft_strncmp(arg[1], "here_doc", 8) != 0)
		my_pipe(arg, &info);
	else
	{
		if (ac != 6)
			return (ft_putstr_fd("Pad argc\n", 2), 0);
		info.str_i = ac - 4;
		my_pipe(arg, &info);
	}
	return (0);
}
