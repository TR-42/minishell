/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:46:36 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 22:57:46 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_lst.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_new_lst_top;
	t_list	*p_new_lst;

	if (lst == NULL)
		return (NULL);
	p_new_lst_top = ft_lstnew(f(lst->content));
	if (p_new_lst_top == NULL)
		return (NULL);
	p_new_lst = p_new_lst_top;
	lst = lst->next;
	while (lst != NULL)
	{
		p_new_lst->next = ft_lstnew(f(lst->content));
		p_new_lst = p_new_lst->next;
		lst = lst->next;
		if (p_new_lst == NULL)
		{
			ft_lstclear(&p_new_lst_top, del);
			return (NULL);
		}
	}
	return (p_new_lst_top);
}
