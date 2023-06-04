/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wildcard_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:40 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 12:21:40 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - free
#include <stdlib.h>

// - MAXPATHLEN
#include <sys/param.h>

#include "ft_string/ft_string.h"

#include "_build_cmd.h"
#include "_filectrl_tools.h"
#include "error_utils.h"

#include "_build_cmd_wildcard.h"

static bool	_free_wcinfo(t_wcinfo info)
{
	free((void *)(info.left_dir));
	free((void *)(info.left_fname));
	free((void *)(info.right_fname));
	free((void *)(info.right_path));
	return (true);
}

// !! ERR_PRINTED
// -> <inherit> search_files
__attribute__((nonnull))
static bool	_search_and_set(
	t_cmd_elem *elem,
	size_t i_wc,
	size_t i_len,
	t_wcinfo info
)
{
	char	*buf;
	size_t	i;

	elem[i_wc].p_malloced = (char *)search_files(info);
	if (elem[i_wc].p_malloced == NULL
		|| *((char **)(elem[i_wc].p_malloced)) == NULL)
	{
		elem[i_wc].type = CMDTYP_NORMAL;
		return (_free_wcinfo(info));
	}
	while (((char **)(elem[i_wc].p_malloced))[elem[i_wc].p_mlc_len] != NULL)
		elem[i_wc].p_mlc_len += 1;
	if (elem[i_wc].p_mlc_len <= 1)
	{
		buf = ((char **)(elem[i_wc].p_malloced))[0];
		free(elem[i_wc].p_malloced);
		elem[i_wc].p_malloced = buf;
		elem[i_wc].p_mlc_len = 0;
	}
	i = 0;
	while (i < i_len)
		elem[i++].type = CMDTYP_VAR_WILDCARD;
	return (_free_wcinfo(info));
}

bool	_set_wcinfo(char *lpath, char *rpath, t_wcinfo *wcinfo)
{
	char	*pos;

	if (!ft_isstrnullempty(lpath))
	{
		wcinfo->left_dir = ft_dirname(lpath);
		wcinfo->left_fname = ft_basename(lpath);
		if (wcinfo->left_dir == NULL || wcinfo->left_fname == NULL)
			return (strerr_ret_false("_set_wcinfo()"));
	}
	if (ft_isstrnullempty(rpath))
		return (true);
	pos = ft_strchr(rpath, '/');
	if (pos == NULL || pos[1] == '\0')
		wcinfo->right_fname = ft_strdup(rpath);
	else
	{
		wcinfo->right_fname = ft_strndup(rpath, pos - rpath);
		wcinfo->right_path = ft_strdup(pos + 1);
		if (wcinfo->right_path == NULL)
			return (strerr_ret_false("_set_wcinfo()"));
	}
	if (wcinfo->right_fname == NULL)
		return (strerr_ret_false("_set_wcinfo()"));
	return (true);
}

// !! ERR_PRINTED
__attribute__((nonnull))
static bool	_set_wildcard_values_seg(
	t_cmd_elem *elems,
	size_t i_start,
	size_t i_next,
	size_t i_wildcard
)
{
	char		*lpath;
	char		*rpath;
	t_wcinfo	wcinfo;
	bool		tf;

	if ((i_next - i_start) == 1)
		return (_search_and_set(elems + i_start, i_wildcard - i_start,
				i_next - i_start, (t_wcinfo){0}));
	if (!get_left_path(elems + i_start, i_wildcard - i_start, &lpath))
		return (strerr_ret_false("_set_wildcard_values_seg()/lpath"));
	if (!get_right_path(elems + i_start, i_wildcard - i_start,
			i_next - i_start, &rpath))
	{
		free(lpath);
		return (strerr_ret_false("_set_wildcard_values_seg()/rpath"));
	}
	tf = _set_wcinfo(lpath, rpath, &wcinfo);
	free(lpath);
	free(rpath);
	return (tf);
}

// !! ERR_PRINTED
// -> (root) for malloc failed
__attribute__((nonnull))
bool	set_wildcard_values(
	t_cmdelmarr *elemarr
)
{
	size_t		i;
	size_t		len;
	t_cmd_elem	*elems;
	size_t		i_wildcard;

	i = 0;
	elems = (t_cmd_elem *)(elemarr->p);
	while (i < elemarr->len)
	{
		len = _one_elem_count(elemarr, i);
		if (_contains_valid_wildcard(elems, i, i + len, &i_wildcard))
		{
			if (!_set_wildcard_values_seg(elems, i, i + len, i_wildcard))
				return (false);
		}
		else if (i_wildcard < (i + len))
			return (errstr_ret_false("_contains_valid_wildcard()",
					"Invalid Wildcard Usage"));
		i += len;
	}
	return (true);
}
