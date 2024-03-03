/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:49:51 by keschouf          #+#    #+#             */
/*   Updated: 2023/02/22 06:50:31 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"

int			checkerror(int fd, char *str);
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
