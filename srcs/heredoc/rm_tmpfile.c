/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:18:43 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 22:51:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - free
#include <stdlib.h>

// - unlink
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "error_utils.h"
#include "heredoc.h"

// !! ERR_PRINTED
// -> (root) for unlink (実行は中断しない)
__attribute__((nonnull))
static int	_rm_tmpfile_from_elems(t_cmd_elem *elemarr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (elemarr[i++].type != CMDTYP_RED_HEREDOC_SAVED)
			continue ;
		if (unlink(elemarr[i - 1].elem_top) != 0)
			strerr_ret_false(elemarr[i - 1].elem_top);
		free((char *)(elemarr[i - 1].elem_top));
		elemarr[i - 1].elem_top = NULL;
	}
	return (0);
}

// !! ERR_PRINTED
// -> <inherit> _rm_tmpfile_from_elems (エラーは出力するものの、dispose段のため処理を続行する)
__attribute__((nonnull))
int	rm_tmpfile(t_cmdarr *cmdarr)
{
	t_cmdelmarr	*elems;
	size_t		i;

	i = 0;
	elems = (t_cmdelmarr *)(cmdarr->p);
	while (i < cmdarr->len)
	{
		_rm_tmpfile_from_elems((t_cmd_elem *)(elems[i].p), elems[i].len);
		i += 1;
	}
	return (0);
}
