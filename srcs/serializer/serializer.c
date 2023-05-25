/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:01:01 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 22:51:54 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ft_is/ft_is.h"

#include "error_utils.h"

#include "serializer.h"
#include "_serializer.h"

// input: 実行後、次の要素の先頭が入る
// !! NO_ERROR
__attribute__((nonnull))
static t_cmd_elem	_take_one_elem(const char **input, t_pars_mde *mode)
{
	t_cmd_elem	v;

	v = (t_cmd_elem){0};
	v.elem_top = *input;
	while (**input != '\0')
	{
		if (_serializer_redirect(input, mode, &v)
			|| _serializer_pipe(input, mode, &v)
			|| _serializer_squote(input, mode, &v)
			|| _serializer_dquote(input, mode, &v)
			|| _serializer_var(input, mode, &v))
			return (v);
		if (*mode == M_NORMAL)
		{
			if (ft_isspace(*((*input)++)))
				return (v);
			else
				v.len += 1;
		}
	}
	return (v);
}

// !! MUST_PRINT_ERROR_IN_CALLER
__attribute__((nonnull))
static bool	_take_elems(t_cmdelmarr *elmarr, const char **input)
{
	t_pars_mde	mode;
	t_cmd_elem	elem;

	mode = M_NORMAL;
	while (**input != '\0')
	{
		if (ft_isspace(**input))
			*input += 1;
		else
		{
			elem = _take_one_elem(input, &mode);
			if (*(elem.elem_top) == '\0')
				break ;
			if (!vect_push_back(elmarr, &elem, NULL))
			{
				vect_dispose(elmarr);
				return (false);
			}
			if (elem.type == CMDTYP_PIPE)
				break ;
		}
	}
	return (true);
}

// !! MUST_PRINT_ERROR_IN_CALLER
__attribute__((nonnull))
static bool	_take_one_cmd(t_cmdarr *v, const char **input)
{
	t_cmdelmarr	cmd;

	cmd = vect_init(16, sizeof(t_cmd_elem));
	if (cmd.p == NULL)
		return (false);
	if (!_take_elems(&cmd, input))
		return (false);
	if (cmd.len == 0 && **input == '\0')
	{
		vect_dispose(&cmd);
		return (true);
	}
	return (vect_push_back(v, &cmd, NULL));
}

// !! ERR_PRINTED
// -> (root) for vect_init
// -> (root) for _take_one_cmd
__attribute__((nonnull))
t_cmdarr	serialize(const char *input)
{
	t_cmdarr	v;

	v = vect_init(16, sizeof(t_cmdelmarr));
	if (v.p == NULL)
	{
		strerr_ret_false("serializer init");
		return (v);
	}
	while (*input != '\0')
	{
		if (!_take_one_cmd(&v, &input))
		{
			strerr_ret_false("serializer push_back");
			dispose_t_cmdarr(&v);
			return (v);
		}
	}
	return (v);
}
