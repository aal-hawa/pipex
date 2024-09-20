/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 19:38:14 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void init_info_main(int ac, char *env, t_info *info)
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
	if (ac != 5)
		return (ft_putstr_fd("Pad argc\n", 2), 0);
	init_info_main(ac, env, &info);
	my_pipe(arg, &info);
	return (0);
}


