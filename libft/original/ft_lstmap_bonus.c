/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:57:24 by kmailleu          #+#    #+#             */
/*   Updated: 2023/11/23 18:12:30 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*first;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	first = ft_lstnew(f(lst->content));
	new = first;
	while (lst != NULL && lst->next != NULL)
	{
		if (new == NULL)
			return (NULL);
		new->next = ft_lstnew(f((lst->next)->content));
		lst = lst->next;
		new = new->next;
	}
	return (first);
}
