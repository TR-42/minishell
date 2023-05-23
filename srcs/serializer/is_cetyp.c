/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cetyp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:25:45 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/20 23:47:40 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

bool	is_cetyp_redirect(t_cmd_elem_type t)
{
	return (t == CMDTYP_RED_APPEND
		|| t == CMDTYP_RED_HEREDOC
		|| t == CMDTYP_RED_HEREDOC_SAVED
		|| t == CMDTYP_RED_IN
		|| t == CMDTYP_RED_OUT);
}

bool	is_cetyp_var_or_normal(t_cmd_elem_type t)
{
	return (t == CMDTYP_NORMAL
		|| t == CMDTYP_QUOTE_VAR
		|| t == CMDTYP_VARIABLE);
}

bool	is_cetyp_terminator(t_cmd_elem_type t)
{
	return (t == CMDTYP_PIPE);
}
