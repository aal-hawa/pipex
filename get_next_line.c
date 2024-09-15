/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:01 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/15 18:33:25 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_char(char *this_string)
{
	if (!this_string)
		return (NULL);
	free(this_string);
	this_string = NULL;
	return (NULL);
}

char	*els_whl_nxt(char **text_buffer, char *returntext, ssize_t bytesreed)
{
	if (bytesreed == 0 && *text_buffer[0])
	{
		returntext = free_char(returntext);
		returntext = ft_strdup_line(*text_buffer, 0);
		*text_buffer = ft_strdup_after_line(*text_buffer);
		if (!*text_buffer[0])
			*text_buffer = free_char(*text_buffer);
	}
	else
	{
		*text_buffer = free_char(*text_buffer);
		returntext = free_char(returntext);
		return (NULL);
	}
	return (returntext);
}

char	*while_next_line(char **text_buffer, int fd, ssize_t bytesreed)
{
	char	*returntext;

	while (bytesreed > 0)
	{
		returntext = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!returntext)
			return (NULL);
		bytesreed = read(fd, returntext, BUFFER_SIZE);
		if (bytesreed > 0)
		{
			returntext[bytesreed] = '\0';
			*text_buffer = ft_strjoin_g(*text_buffer, returntext);
			returntext = free_char(returntext);
			returntext = ft_strdup_line(*text_buffer, 1);
			if (returntext)
			{
				*text_buffer = ft_strdup_after_line(*text_buffer);
				break ;
			}
		}
		else
			returntext = els_whl_nxt(text_buffer, returntext, bytesreed);
	}
	return (returntext);
}

char	*get_next_line(int fd)
{
	static char	*text_buffer;
	ssize_t		bytesreed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!text_buffer)
	{
		text_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!text_buffer)
			return (NULL);
		text_buffer[0] = '\0';
	}
	bytesreed = 1;
	return (while_next_line(&text_buffer, fd, bytesreed));
}
