/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:36:55 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 17:29:48 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_mem/ft_mem.h"
#include "ft_string/ft_string.h"

#include "error_utils.h"
#include "_build_cmd.h"

// !! NO_ERROR
// TODO: 環境変数を用いた形に書き換える
__attribute__((nonnull(1)))
static size_t	_get_elem_str_len(const t_cmd_elem *elem, char *const*envp)
{
	if (elem->type == CMDTYP_VARIABLE || elem->type == CMDTYP_QUOTE_VAR)
	{
		if (envp == NULL)
			return (elem->len + 1);
		if (elem->p_malloced == NULL)
			return (0);
		return (ft_strlen(elem->p_malloced));
	}
	else
		return (elem->len);
}

// !! NO_ERROR
// TODO: 環境変数を用いた形に書き換える
__attribute__((nonnull(1, 2)))
static size_t	_set_elem_str(char *dst, const t_cmd_elem *elem,
	char *const *envp)
{
	if (elem->type == CMDTYP_VARIABLE || elem->type == CMDTYP_QUOTE_VAR)
	{
		if (envp == NULL)
		{
			ft_memcpy(dst, elem->elem_top - 1, elem->len + 1);
			return (elem->len + 1);
		}
		if (elem->p_malloced == NULL)
			return (0);
		ft_memcpy(dst, elem->p_malloced, ft_strlen(elem->p_malloced));
		return (elem->len);
	}
	else
	{
		ft_memcpy(dst, elem->elem_top, elem->len);
		return (elem->len);
	}
}

// !! MUST_PRINT_ERROR_IN_CALLER (malloc error)
__attribute__((nonnull(1)))
static char	*_gen_argv_one_str(const t_cmd_elem *elem, size_t len,
	char *const *envp)
{
	size_t	str_len;
	size_t	i;
	char	*str;

	str_len = 0;
	i = 0;
	str = NULL;
	while (i < len)
		str_len += _get_elem_str_len(elem + i++, envp);
	if (0 < len)
		str = (char *)malloc(str_len + 1);
	if (str == NULL)
		return (NULL);
	str[str_len] = 0;
	i = 0;
	str_len = 0;
	while (i < len)
		str_len += _set_elem_str(str + str_len, elem + i++, envp);
	return (str);
}

// !! ERR_PRINTED
// -> (root) for _gen_argv_one_str
// -> (len <= i の場合にNULLが返る -> バリデーション済みのため到達しない)
__attribute__((nonnull(1, 2)))
char	*_get_argv_one(const t_cmdelmarr *elemarr, size_t *i_start,
	char *const *envp)
{
	size_t		current_seg_len;
	t_cmd_elem	*elem;
	char		*tmp;

	while (*i_start < elemarr->len)
	{
		elem = (t_cmd_elem *)(elemarr->p) + *i_start;
		current_seg_len = _one_elem_count(elemarr, *i_start);
		*i_start += current_seg_len;
		if (!is_cetyp_var_or_normal(elem->type))
			continue ;
		tmp = _gen_argv_one_str(elem, current_seg_len, envp);
		if (tmp == NULL)
			strerr_ret_false("_get_argv_one()/malloc");
		return (tmp);
	}
	return (NULL);
}

// ここに来る段階では、既にバリデーションが完了していると期待する
//   - 0 < argcは確定している
//   - リダイレクトの引数は正常に設定されている
// !! ERR_PRINTED
// -> (root) for _get_argc
// -> (root) for malloc
// -> <inherit> _get_argv_one
__attribute__((nonnull(1)))
char	**build_cmd(t_cmdelmarr *elemarr, char *const *envp)
{
	int			argc;
	char		**argv;
	int			i_argv;
	size_t		i_elemarr;

	argc = _get_argc(elemarr);
	if (argc <= 0)
	{
		errstr_ret_false("build_cmd()/_get_argc()", "too many args");
		return (NULL);
	}
	argv = (char **)malloc(sizeof(char **) * ((size_t)argc + 1));
	if (argv == NULL)
	{
		strerr_ret_false("build_cmd()/malloc");
		return (NULL);
	}
	argv[argc] = NULL;
	i_argv = 0;
	i_elemarr = 0;
	while (i_argv < argc)
		argv[i_argv++] = _get_argv_one(elemarr, &i_elemarr, envp);
	return (argv);
}
