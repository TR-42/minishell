/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmpfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:58:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 13:44:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - NULL
#include <stddef.h>

// - stderror
#include <string.h>

// - access
// - write
// - STDERR_FILENO
#include <unistd.h>

// - open
#include <fcntl.h>

#include "ft_mem/ft_mem.h"
#include "ft_printf/ft_printf.h"
#include "ft_string/ft_string.h"

#include "_env_util.h"
#include "heredoc.h"

#define EMSG_PATHJOIN "minishell: failed to generate path to tmp file"

#define TMPFN_HEAD "minish_heredoc_"
#define TMPFN_MAXLEN 10

static size_t	_get_tmpfile_path_buf(char *const *envp, char **fname_save)
{
	const char	*tmpdir;
	size_t		tmpdir_len;

	if (envp == NULL || fname_save == NULL)
		return (0);
	tmpdir = get_env_value(envp, "TMPDIR");
	if (tmpdir == NULL || access(tmpdir, R_OK | W_OK) != 0)
		tmpdir = "/tmp";
	tmpdir_len = ft_strlen(tmpdir);
	*fname_save = ft_calloc(
			tmpdir_len + sizeof(TMPFN_HEAD) + TMPFN_MAXLEN + 1, 1);
	if (*fname_save == NULL)
		return (0);
	ft_memcpy(*fname_save, tmpdir, tmpdir_len);
	if (tmpdir[tmpdir_len - 1] != '/')
		(*fname_save)[tmpdir_len++] = '/';
	ft_memcpy(*fname_save + tmpdir_len, TMPFN_HEAD, sizeof(TMPFN_HEAD));
	return (tmpdir_len + sizeof(TMPFN_HEAD));
}

// (internal)
// - false: char change needed
// - true: char already changed
static bool	_set_next_fname(char *fname_btm)
{
	if (*fname_btm == '_')
		return (false);
	if (_set_next_fname(fname_btm - 1))
		return (true);
	if (*fname_btm == 0)
		*fname_btm = '0';
	else if (*fname_btm == '9')
		*fname_btm = 'a';
	else if (*fname_btm == 'z')
		*fname_btm = 'A';
	else if (*fname_btm == 'Z')
	{
		*fname_btm = '0';
		return (false);
	}
	else
		*fname_btm += 1;
	return (true);
}

// tmpファイルを作成する。書き込み専用で作成し、基本的に呼び出し元で責任をもって削除する。
// `fname_save`にはファイルパスが記録される。
int	create_tmpfile(char *const *envp, char **fname_save)
{
	int		fd;
	size_t	fname_head_pos;
	char	*c;

	fname_head_pos = _get_tmpfile_path_buf(envp, fname_save);
	if (fname_head_pos == 0)
		return ((write(STDERR_FILENO, EMSG_PATHJOIN,
					sizeof(EMSG_PATHJOIN) - 1) * 0) - 1);
	fd = -1;
	c = *fname_save + fname_head_pos;
	while (fd < 0 && (c - *fname_save - fname_head_pos) < TMPFN_MAXLEN)
	{
		if (!_set_next_fname(c))
		{
			c += 1;
			continue ;
		}
		fd = open(*fname_save, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd < 0 && errno != EEXIST)
			return ((ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
						*fname_save, strerror(errno)) * 0) - 1);
	}
	return (fd);
}
