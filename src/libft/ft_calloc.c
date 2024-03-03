/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:34:26 by kschouft          #+#    #+#             */
/*   Updated: 2023/04/21 17:33:31 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;
	int		i;
	int		j;

	i = 0;
	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	j = nmemb * size;
	mem = malloc(j);
	if (mem == NULL)
		return (0);
	while (j > 0)
	{
		mem[i] = 0;
		i++;
		j--;
	}
	return (mem);
}
