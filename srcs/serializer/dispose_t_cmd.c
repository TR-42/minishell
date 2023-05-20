/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_t_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:50 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 01:14:08 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "serializer.h"

static void	_vect_dispose(void *vect)
{
	vect_dispose((t_vect *)vect);
}

// return: always 0
int	dispose_t_cmdarr(t_cmdarr *cmd)
{
	if (cmd == NULL)
		return (0);
	vect_dispose_each(cmd, _vect_dispose);
	return (0);
}
