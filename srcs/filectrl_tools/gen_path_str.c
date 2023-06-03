/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_path_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:05:21 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 02:53:30 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - size_t
// - NULL
#include <stddef.h>

// - malloc
#include <stdlib.h>

#include "ft_string/ft_string.h"
#include "ft_mem/ft_mem.h"

#include "_filectrl_tools.h"

static void	_set_ldir(
	char *buf,
	const char *ldir,
	size_t ldir_len
)
{
	if (ldir_len == 0)
		return ;
	ft_memcpy(buf, ldir, ldir_len);
	if (buf[ldir_len - 1] != '/')
		buf[ldir_len - 1] = '/';
}

static void	_set_rdir(
	char *buf,
	const char *rdir,
	size_t rdir_len
)
{
	buf[rdir_len] = '\0';
	if (rdir_len == 0)
		return ;
	if (buf[0] != '/')
		*(buf++) = '/';
	ft_memcpy(buf, rdir, rdir_len);
}

__attribute__((nonnull(2)))
char	*gen_path_str(
	const char *ldir,
	const char *fname,
	const char *rdir
)
{
	size_t	ldir_len;
	size_t	rdir_len;
	size_t	fname_len;
	char	*buf;

	ldir_len = 0;
	if (ldir != NULL)
		ldir_len += ft_strlen(ldir);
	if (0 < ldir_len && ldir[ldir_len - 1] != '/')
		ldir_len += 1;
	rdir_len = 0;
	if (rdir != NULL)
		rdir_len += ft_strlen(rdir);
	if (0 < rdir_len && rdir[0] != '/')
		rdir_len += 1;
	fname_len = ft_strlen(fname);
	buf = malloc(ldir_len + fname_len + rdir_len + 1);
	if (buf == NULL)
		return (NULL);
	_set_ldir(buf, ldir, ldir_len);
	ft_memcpy(buf + ldir_len, fname, fname_len);
	_set_rdir(buf + ldir_len + fname_len, rdir, rdir_len);
	return (buf);
}
