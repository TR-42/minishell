/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmpfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:58:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 22:51:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - NULL
#include <stddef.h>

// - free
#include <stdlib.h>

// - access
#include <unistd.h>

// - open
#include <fcntl.h>

#include "ft_mem/ft_mem.h"
#include "ft_printf/ft_printf.h"
#include "ft_string/ft_string.h"

#include "_env_util.h"
#include "heredoc.h"

#include "error_utils.h"

#define EMSG_PATHJOIN "failed to generate path to tmp file"

#define TMPFN_HEAD "minish_heredoc_"
#define TMPFN_MAXLEN 10

// !! MUST_PRINT_ERROR_IN_CALLER
__attribute__((nonnull))
static size_t	_get_tmpfile_path_buf(char *const *envp, char **fname_save)
{
	const char	*tmpdir;
	size_t		tmpdir_len;

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
// !! NO_ERROR
__attribute__((nonnull))
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

static int	_err_chk_proc(int fd, char **fname_save)
{
	if (0 <= fd)
		return (fd);
	strerr_ret_false(*fname_save);
	free(*fname_save);
	*fname_save = NULL;
	return (-1);
}

// tmpファイルを作成する。書き込み専用で作成し、基本的に呼び出し元で責任をもって削除する。
// `fname_save`にはファイルパスが記録される。
// !! ERR_PRINTED
// -> (root) for _get_tmpfile_path_buf (パス文字列生成失敗)
// -> (root) for open (ファイル作成失敗)
__attribute__((nonnull))
int	create_tmpfile(char *const *envp, char **fname_save)
{
	int		fd;
	size_t	fname_head_pos;
	char	*c;

	fname_head_pos = _get_tmpfile_path_buf(envp, fname_save);
	if (fname_head_pos == 0)
		return (errstr_ret_false("(heredoc)", EMSG_PATHJOIN));
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
			break ;
	}
	return (_err_chk_proc(fd, fname_save));
}
