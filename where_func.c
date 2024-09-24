/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:24:47 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/24 18:56:55 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	env_data(char **envp, char **env)
{
	int i;

	i = 0;
	*env = NULL;
	if (envp)
	{
		while (envp[i])
		{
			if(ft_strncmp(envp[i], "PATH=", 5) == 0)
			{
				*env = &envp[i][5];
				break ;
			}
			i++;
		}
	}
}

char *get_from_env(char *env, char *str, t_info *info)
{
	int i;
	char **env_split;
	char *error_m;
	char	*joined;
	
	if (!env)
		return (NULL);
	i = 0;
	env_split = ft_split(env, ':', info);
	if (!env_split)
		return (NULL);
	while(env_split[i])
	{
		joined = ft_strjoin(env_split[i], str, 1);
		if (!access(joined, R_OK))
			return (free_split(env_split, info->i_split), joined);
		free_char(joined);
		i++;
	}
	free_split(env_split, info->i_split);
	error_m = ft_strjoin("zsh: command not found: ", str, 0);
	ft_putstr_fd(error_m, 2, 1);
	write(2, "\n", 1);
	return (NULL);
}
