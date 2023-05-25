/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:32:10 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/16 21:37:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

__attribute__((nonnull))
t_cmd_i_inval	is_valid_input(const t_cmdarr *cmdarr)
{
	t_cmd_i_inval	v;
	t_cmdelmarr		*p;

	v = (t_cmd_i_inval){0};
	p = (t_cmdelmarr *)(cmdarr->p);
	while (v.index < cmdarr->len)
	{
		v.type = is_valid_cmd(p + v.index, (v.index + 1) == cmdarr->len);
		if (v.type != CMD_INVAL_NO_ERR)
			break ;
		v.index += 1;
	}
	return (v);
}
