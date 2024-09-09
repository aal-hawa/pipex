/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:05:33 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/09 15:37:34 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	len_sub(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	count_sub(char const *s, char c)
{
	size_t	count;
	int		in_sub;

	count = 0;
	in_sub = 0;
	while (*s)
	{
		if (*s != c && !in_sub)
		{
			in_sub = 1;
			count++;
		}
		else if (*s == c)
			in_sub = 0;
		s++;
	}
	return (count);
}

void	free_split(char **dst, size_t i)
{
	while (i > 0)
		free(dst[--i]);
	free(dst);
}

int	sub_split(char **dst, char const *s, char c)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (*s)
	{
		j = 0;
		if (*s != c)
		{
			dst[i] = (char *)malloc(sizeof(char) * (len_sub(s, c) + 1));
			if (!dst[i])
			{
				free_split(dst, i);
				return (1);
			}
			while (*s && *s != c)
				dst[i][j++] = *s++;
			dst[i++][j] = '\0';
		}
		else
			s++;
	}
	dst[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	len;

	if (!s)
		return (NULL);
	len = count_sub(s, c);
	dst = (char **)malloc(sizeof(char *) * (len + 1));
	if (!dst)
		return (NULL);
	if (sub_split(dst, s, c) != 0)
		return (NULL);
	return (dst);
}
