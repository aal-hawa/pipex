/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/14 16:20:45 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **arg, char **envp)
{
	int i;
	char *env;
	i = 0;
	// int ret;

	// ret = system("grip");
	// return (0);
    // // Check the return value and print the error message
    // if (ret == -1) {
    //     printf("Failed to execute the command\n");
    // } else {
    //     printf("Command executed with return value: %d\n", ret);
    // }
	// return (0);
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
	my_pipe(ac, arg, env);
	return (0);
}

