/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:39:50 by kschouft          #+#    #+#             */
/*   Updated: 2024/03/03 21:56:27 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (size == 0 && (!src || !dst))
		return (0);
	if (size < ft_strlen(dst))
		k = size + ft_strlen(src);
	else
		k = ft_strlen(dst) + ft_strlen(src);
	while (dst[i] != '\0')
		i++;
	if (size-- > 0)
	{
		while (src[j] != '\0' && i < size)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (k);
}
