/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_tmpfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:18:43 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 14:38:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - free
#include <stdlib.h>

// - strerror
#include <string.h>

// - STDERR_FILENO
// - unlink
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "heredoc.h"

static int	_rm_tmpfile_from_elems(t_cmd_elem *elemarr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (elemarr[i++].type != CMDTYP_RED_HEREDOC_SAVED)
			continue ;
		if (unlink(elemarr[i - 1].elem_top) != 0)
			ft_dprintf(STDERR_FILENO, "minishell: rm_heredoc_tmpfile(%s): %s",
				elemarr[i - 1].elem_top, strerror(errno));
		free((char *)(elemarr[i - 1].elem_top));
		elemarr[i - 1].elem_top = NULL;
	}
	return (0);
}

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
