/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:58:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/20 19:30:49 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *str, char first_split, char last_split)
{
	char	*dst;
	size_t	i;
	size_t	j;
	int		is_got_f;

	is_got_f = 0;
	dst = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
	return (dst[j] = '\0', free(str), dst);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if ((unsigned char)*str1 != (unsigned char)*str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		if (!(unsigned char)*str1)
			return (0);
		str1++;
		str2++;
		n--;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2, int is_path)
{
	size_t	len;
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 2));
	i = 0;
	j = 0;
	if (!dst)
		return (NULL);
	while (s1[i])
		dst[j++] = s1[i++];
	if (is_path == 1)
		dst[j++] = '/';
	i = 0;
	while (s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	free_char(s);
}
