/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:01:01 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/05 23:11:24 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "ft_is/ft_is.h"

#include "serializer.h"
#include "_serializer.h"

// input: 実行後、次の要素の先頭が入る
static t_cmd_elem	_take_one_elem(const char **input, t_pars_mde *mode)
{
	t_cmd_elem	v;

	v = (t_cmd_elem){0};
	v.elem_top = *input;
	while (**input != '\0')
	{
		if (_serializer_squote(input, mode, &v)
			|| _serializer_dquote(input, mode, &v)
			|| _serializer_var(input, mode, &v))
			return (v);
		if (mode == M_NORMAL)
		{
			if (ft_isspace(*((*input)++)))
				return (v);
			else
				v.len += 1;
		}
	}
	return (v);
}

static bool	_take_one_cmd(t_cmdarr *v, const char **input)
{
	t_cmdelmarr	cmd;
	t_pars_mde	mode;
	t_cmd_elem	elem;

	cmd = vect_init(16, sizeof(t_cmd_elem));
	while (**input != '\0' && (mode == M_NORMAL && **input != '|'))
	{
		if (ft_isspace(**input))
			*input += 1;
		else
		{
			elem = _take_one_elem(input, &mode);
			if (!vect_push_back(&cmd, &elem, NULL))
			{
				perror("serializer/take_one_cmd push_back");
				vect_dispose(&cmd);
				return (false);
			}
			if (elem.type == CMDTYP_PIPE)
				break ;
		}
	}
	return (vect_push_back(v, &cmd, NULL));
}

t_cmdarr	serialize(const char *input)
{
	t_cmdarr	v;

	v = vect_init(16, sizeof(t_cmdelmarr));
	if (v.p == NULL)
	{
		perror("serializer init");
		return (v);
	}
	while (*input != '\0')
	{
		if (!_take_one_cmd(&v, &input))
		{
			perror("serializer push_back");
			dispose_t_cmdarr(&v);
			return (v);
		}
	}
	return (v);
}
