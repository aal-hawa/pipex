/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/09 17:30:46 by aal-hawa         ###   ########.fr       */
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
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = &envp[i][5];
			break ;
		}
		i++;
	}
	if (ac != 5)
		return (0);
	my_pipe(ac, arg, env);
	return (0);
}

// int	main(int ac, char **arg)
// {
// 	int	fd_file;
// 	char *res;
	
// 	if (ac  != 5)
// 	return (0);
// 	fd_file = open_file_r(arg[1]);
// 	if (fd_file == -1)
// 	{
// 		perror("from open file");
// 		return (1);
// 	}
// 	res = read_file(fd_file);
// 	if (!res)
// 	{
// 		close(fd_file);
// 		printf ("close from main\n");
// 		return (1);
// 	}
// 	close(fd_file);
// 	res = my_pipe(arg[2], res);
// 	if (!res)
// 		return (1);
// 	res = my_pipe(arg[3], res);
// 	if (!res)
// 		return (1);
// 	fd_file = open_file_w(arg[4]);
// 	if (fd_file == -1)
// 	{
// 		perror("from open file");
// 		return (1);
// 	}
// 	write (fd_file, res, sizeof(res));
// 	return (0);
// }
