/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/15 18:34:37 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **arg, char **envp)
{
	int i;
	char *env;
	i = 0;
	
	if (!envp)
		env = NULL;
	else
	{
		while (envp[i])
		{
			if(ft_strncmp(envp[i], "PATH=", 5) == 0)
			{
				env = &envp[i][5];
				break ;
			}
			i++;
		}
	}
	if (ac != 5)
		return (0);
	my_pipe(ac, arg, env, ac - 3);
	return (0);
}


