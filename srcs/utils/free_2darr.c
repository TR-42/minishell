/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2darr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:03:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/30 20:24:18 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "utils.h"

// !! NO_ERROR
void	*free_2darr(void ***p_to_2darr)
{
	size_t	i;

	if (p_to_2darr == NULL || *p_to_2darr == NULL)
		return (NULL);
	i = 0;
	while ((*p_to_2darr)[i] != NULL)
		free((*p_to_2darr)[i++]);
	free(*p_to_2darr);
	*p_to_2darr = NULL;
	return (NULL);
}
