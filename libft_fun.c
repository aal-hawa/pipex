/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:58:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/07 19:12:07 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str,char first_split, char last_split)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	len;
	int	is_got_f;

	is_got_f = 0;
	len = ft_strlen(str);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((is_got_f == 1 && str[i] != last_split) || (is_got_f == 0 &&  str[i] == first_split))
		{
			is_got_f = 1;
			dst[j++] = str[i++];
		}
		else if (is_got_f == 1 && str[i] == last_split)
			break;
		else
			i++;
	}
	dst[j] = '\0';
	free(str);
	return (dst);
}
