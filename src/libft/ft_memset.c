/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschouft <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:37:51 by kschouft          #+#    #+#             */
/*   Updated: 2022/11/14 12:56:12 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)b;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (b);
}
