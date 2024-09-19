/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/19 18:50:00 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **arg, char **envp)
{
	int i;
	char *env;
	info_t info;

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
	info.ac = ac;
	info.env = env;
	info.str_i = ac - 3;
	my_pipe(arg, &info);
	return (0);
}


