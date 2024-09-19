/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:24:47 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/18 13:33:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char *get_from_env(char *env, char *str)
{
	int i;
	char **env_split;
	
	if (!env)
		return (NULL);
	i = 0;
	env_split = ft_split(env, ':');
	if (!env_split)
		return (NULL);
	while(env_split[i])
	{
		if (!access(ft_strjoin(env_split[i], str, 1) , R_OK))
		{
			return (ft_strjoin(env_split[i], str, 1));
		}
		i++;
	}
	char *error_m = ft_strjoin("zsh: command not found: ", str, 0);
	i= 0;
	while (error_m[i])
	{
		write(1, &error_m[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (NULL);
}
