/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 00:45:54 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 22:57:19 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_lst.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p_next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		p_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = p_next;
	}
}
