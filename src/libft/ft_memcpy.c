/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:37:28 by kschouft          #+#    #+#             */
/*   Updated: 2023/04/21 17:17:10 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	size;

	size = 0;
	if (dst || src)
	{
		while (size < n)
		{
			((unsigned char *)dst)[size] = ((unsigned char *)src)[size];
			size++;
		}
		return (dst);
	}
	return (NULL);
}
