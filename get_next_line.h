/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:35:19 by aal-hawa          #+#    #+#             */
/*   Updated: 2024/09/18 13:44:13 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlen_line(const char *s);
char	*ft_strdup_line(char *str, int eof);
char	*ft_strdup_after_line(char *str);
char	*ft_strjoin_g(char *s1, char *s2, int *is_done);
char	*free_char(char *this_string);

#endif