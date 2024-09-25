/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:34:01 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/23 16:39:24 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "pipex.h"

char	*free_char(char *this_string)
{
	if (!this_string)
		return (NULL);
	free(this_string);
	this_string = NULL;
	return (NULL);
}

char	*while_next_line(char **text_buffer, ssize_t bytesreed, int *is_done,
		t_info *info)
{
	char	returntext[2];

	while (1)
	{
		bytesreed = read(0, returntext, 1);
		if (bytesreed > 0)
		{
			returntext[bytesreed] = '\0';
			*text_buffer = ft_strjoin_g(*text_buffer, returntext, is_done,
					info);
			if (*is_done == 1)
				break ;
		}
	}
	return (*text_buffer);
}

char	*get_next_line(t_info *info)
{
	char	*text_buffer;
	ssize_t	bytesreed;
	int		is_done;

	is_done = 0;
	text_buffer = malloc(sizeof(char) * (1));
	if (!text_buffer)
		return (NULL);
	text_buffer[0] = '\0';
	bytesreed = 1;
	return (while_next_line(&text_buffer, bytesreed, &is_done, info));
}
