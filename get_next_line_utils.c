/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:51 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/22 20:23:05 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


int last_letters(char *str, int *is_done, t_info *info)
{
	int j = ft_strlen(str) - info->i_limiter;
	if (j < 0)
		return (0);
	if (ft_strncmp(&str[j], info->limiter, info->i_limiter) == 0)
	{
		if (j == 0 || str[j - 1] == '\n')
			return (is_done[0] = 1, 1);
	}
	return (0);
}

char	*ft_strjoin_g(char *s1, char *s2, int *is_done, t_info *info)
{
	size_t	len;
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	if (!dst)
		return (NULL);
	while (s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	free_char(s1);
	if (last_letters(dst, is_done, info) == 1)
		while (info->i_limiter-- > 0)
			dst[j--] = '\0';
	return (dst);
}
