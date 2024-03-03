/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschouft <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 02:43:13 by kschouft          #+#    #+#             */
/*   Updated: 2022/11/28 12:13:49 by kschouft         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst && del)
	{
		tmp = *lst;
		while (*lst)
		{
			tmp = (*lst)->next;
			(*del)((*lst)->content);
			free(*lst);
			(*lst) = tmp;
		}
	}
}
