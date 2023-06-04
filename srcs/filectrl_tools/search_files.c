/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:47:38 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 09:37:20 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "ft_string/ft_string.h"
#include "ft_vect/ft_vect.h"

#include "_filectrl_tools.h"
#include "error_utils.h"

typedef struct dirent	t_dent;

__attribute__((nonnull(1)))
static bool	_match_chk(
	const char *fname,
	const char *l_pat,
	const char *r_pat
)
{
	size_t	lpat_len;
	size_t	rpat_len;
	size_t	fname_len;

	lpat_len = 0;
	rpat_len = 0;
	fname_len = ft_strlen(fname);
	if (!ft_isstrnullempty(l_pat))
	{
		lpat_len = ft_strlen(l_pat);
		if (fname_len < lpat_len || ft_strncmp(fname, l_pat, lpat_len) != 0)
			return (false);
	}
	if (!ft_isstrnullempty(r_pat))
	{
		rpat_len = ft_strlen(r_pat);
		if (fname_len < (lpat_len + rpat_len)
			|| ft_strncmp(fname + fname_len - rpat_len, r_pat, rpat_len))
			return (false);
	}
	return (true);
}

static char	*_is_pat_matched(t_wcinfo wcinfo, const t_dent *dent)
{
	char	*buf;

	if (ft_isstrnullempty(wcinfo.left_fname)
		&& ft_isstrnullempty(wcinfo.right_fname)
		&& ft_isstrnullempty(wcinfo.right_path))
		return (gen_path_str(wcinfo.left_dir, dent->d_name, NULL));
	if (!ft_isstrnullempty(wcinfo.right_path) && dent->d_type != DT_DIR)
		return (NULL);
	if (!_match_chk(dent->d_name, wcinfo.left_fname, wcinfo.right_fname))
		return (NULL);
	buf = gen_path_str(wcinfo.left_dir, dent->d_name, wcinfo.right_path);
	if (ft_isstrnullempty(wcinfo.right_path) || access(buf, F_OK) == 0)
		return (buf);
	free(buf);
	return (NULL);
}

__attribute__((nonnull))
static t_vect	_pick_matched_fname(
	DIR *dir,
	t_wcinfo wcinfo
)
{
	t_vect	vect;
	t_dent	*dent;
	char	*str;
	int		_errno;

	vect = vect_init(32, sizeof(char *));
	while (vect.p != NULL)
	{
		dent = readdir(dir);
		if (dent == NULL)
			return (vect);
		if (wcinfo.left_fname != NULL && wcinfo.left_fname[0] != '.'
			&& dent->d_name[0] == '.')
			continue ;
		str = _is_pat_matched(wcinfo, dent);
		_errno = errno;
		if (_errno != 0 || (str != NULL && !vect_append_ptr(&vect, str)))
		{
			free(str);
			if (_errno != 0)
				errno = _errno;
			return (vect);
		}
	}
	return (vect);
}

// !! ERR_PRINTED
// -> (root) for opendir
// -> (root) for _pick_matched_fname (vect_init / readdir)
char	**search_files(
	t_wcinfo info
)
{
	DIR			*dir;
	int			_errno;
	t_vect		vect;
	const char	*ldir_to_open;

	ldir_to_open = info.left_dir;
	if (ft_isstrnullempty(ldir_to_open))
		ldir_to_open = ".";
	dir = opendir(ldir_to_open);
	if (dir == NULL)
		return (strerr_ret_null("search_files/opendir"));
	errno = 0;
	vect = _pick_matched_fname(dir, info);
	_errno = errno;
	closedir(dir);
	if (_errno != 0)
	{
		vect_dispose_ptrarr(&vect);
		return (strerr_errno_ret_null("search_files", _errno));
	}
	if (0 < vect.len)
		return ((char **)(vect.p));
	vect_dispose(&vect);
	return (NULL);
}
