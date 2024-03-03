/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschouft <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:42:47 by kschouft          #+#    #+#             */
/*   Updated: 2022/11/28 11:18:30 by kschouft         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
	{
		ft_lstclear(&lst, del);
		ft_lstclear(&tmp, del);
	}
	new = tmp;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&tmp, del);
		}
		lst = lst->next;
		ft_lstadd_back(&new, tmp);
	}
	return (new);
}
