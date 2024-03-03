/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:38:59 by keschouf          #+#    #+#             */
/*   Updated: 2023/04/01 02:13:03 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


char		*readline(char *str, int fd);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
void		*ft_memmove(void *dst, const void *src, size_t n);
int			ft_strchr(const char *s, int c);
char		*cut_line(char **str, int pos);
char		*no_new_line(char **str);
char		*get_next_line(int fd);

#endif
