/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschouft <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:37:09 by kschouft          #+#    #+#             */
/*   Updated: 2022/11/14 09:37:10 by kschouft         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ca;

	str = (unsigned char *)s;
	ca = (unsigned char)c;
	while (0 < n--)
	{
		if (*str == ca)
			return (str);
		str++;
	}
	return (NULL);
}
