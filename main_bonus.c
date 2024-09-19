/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:34:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/18 12:53:15 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **arg, char **envp)
{
	int i;
	char *env;
	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = &envp[i][5];
			break ;
		}
		i++;
	}
	if (ac < 5)
		return (0);
	if (ft_strncmp(arg[1], "here_doc", 8) != 0)
		my_pipe(ac, arg, env, ac - 3);
	else
	{
		if (ac != 6)
			return (0);
		my_pipe(ac, arg, env, ac - 4);
	}	
	return (0);
}
