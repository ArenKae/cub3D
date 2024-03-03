/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:37:42 by kschouft          #+#    #+#             */
/*   Updated: 2023/04/21 17:13:33 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*t1;
	char	*t2;

	t1 = (char *)src;
	t2 = (char *)dst;
	if (t1 < t2)
		while (n-- > 0)
			t2[n] = t1[n];
	else
		ft_memcpy(t2, t1, n);
	return (dst);
}
