/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_t_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:50 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/05 22:45:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "serializer.h"

static void	_vect_dispose(void *vect)
{
	vect_dispose((t_vect *)vect);
}

void	dispose_t_cmdarr(t_cmdarr *cmd)
{
	if (cmd == NULL)
		return ;
	vect_dispose_each(cmd, _vect_dispose);
}
