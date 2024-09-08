/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:35:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/08 14:31:18 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//./pipex file1 cmd1 cmd2 file2
int	main(int ac, char **arg, char **envp)
{
	// char *res;
	int i;
	char *env;
	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = &envp[i][5];
			// printf("env:  %s\n", env);
		}
		i++;
	}
	// access()
	if (ac  != 5)
	return (0);
	my_pipe(arg, env);
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
