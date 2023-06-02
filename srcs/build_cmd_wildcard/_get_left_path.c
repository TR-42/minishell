/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_left_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:11:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 00:21:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_build_cmd.h"
#include "_filectrl_tools.h"

#include "_build_cmd_wildcard.h"

// !! MUST_PRINT_ERROR_IN_CALLER (malloc error)
__attribute__((nonnull))
char	*get_left_path(
	t_cmd_elem *elems,
	size_t i_wildcard
)
{
	char		*path;
	size_t		tmp;
	t_cmdelmarr	elemarr;

	if (i_wildcard == 0)
		return (NULL);
	elemarr = (t_cmdelmarr){0};
	elemarr.len = i_wildcard;
	elemarr.elemsize = sizeof(t_cmd_elem);
	elemarr.p = (void *)elems;
	tmp = 0;
	path = _get_argv_one(&elemarr, &tmp);
	if (path == NULL)
		return (NULL);
	return (ft_dirname(path));
}
