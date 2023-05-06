/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_pipe_red.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/07 01:24:55 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_serializer.h"

// return: Elementが終了するかどうか
bool	_serializer_redirect(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (*mode != M_NORMAL || (**input != '<' && **input != '>'))
		return (false);
	if (0 < v->len)
		return (true);
	v->len = 1;
	if ((*input)[0] == '<' && (*input)[1] == '<')
		v->type = CMDTYP_RED_HEREDOC;
	else if ((*input)[0] == '<')
		v->type = CMDTYP_RED_IN;
	else if ((*input)[0] == '>' && (*input)[1] == '>')
		v->type = CMDTYP_RED_APPEND;
	else
		v->type = CMDTYP_RED_OUT;
	if (v->type == CMDTYP_RED_APPEND || v->type == CMDTYP_RED_HEREDOC)
		v->len = 2;
	*input += v->len;
	return (true);
}

// return: Elementが終了するかどうか
bool	_serializer_pipe(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_NORMAL || **input != '|')
		return (false);
	v->type = CMDTYP_PIPE;
	v->len = 1;
	*input += 1;
	return (true);
}
