/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:36:55 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 12:21:00 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_mem/ft_mem.h"
#include "ft_string/ft_string.h"

#include "error_utils.h"
#include "validator.h"
#include "_build_cmd.h"

// !! NO_ERROR
__attribute__((nonnull(1)))
static size_t	_get_elem_str_len(const t_cmd_elem *elem)
{
	if (elem->p_malloced != NULL)
		return (ft_strlen(elem->p_malloced));
	else if (is_cetyp_var(elem->type))
		return (0);
	else
		return (elem->len);
}

// !! NO_ERROR
__attribute__((nonnull(1, 2)))
static size_t	_set_elem_str(char *dst, const t_cmd_elem *elem)
{
	size_t	len;

	if (elem->p_malloced != NULL)
	{
		len = ft_strlen(elem->p_malloced);
		ft_memcpy(dst, elem->p_malloced, len);
		return (len);
	}
	else if (is_cetyp_var(elem->type))
		return (0);
	else
	{
		ft_memcpy(dst, elem->elem_top, elem->len);
		return (elem->len);
	}
}

// !! MUST_PRINT_ERROR_IN_CALLER (malloc error)
__attribute__((nonnull(1)))
static char	*_gen_argv_one_str(const t_cmd_elem *elem, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*str;

	str_len = 0;
	i = 0;
	str = NULL;
	while (i < len)
		str_len += _get_elem_str_len(elem + i++);
	if (0 < len)
		str = (char *)malloc(str_len + 1);
	if (str == NULL)
		return (NULL);
	str[str_len] = 0;
	i = 0;
	str_len = 0;
	while (i < len)
		str_len += _set_elem_str(str + str_len, elem + i++);
	return (str);
}

// !! ERR_PRINTED
// -> (root) for _gen_argv_one_str
// -> (len <= i の場合にNULLが返る -> バリデーション済みのため到達しない)
__attribute__((nonnull(1, 2)))
char	*_get_argv_one(const t_cmdelmarr *elemarr, size_t *i_start)
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
		tmp = _gen_argv_one_str(elem, current_seg_len);
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
// -> <inherit> set_var_values
// -> <inherit> validate_red_fname (validation error)
// -> <inherit> elems_make_flat
// -> (root) for _get_argc
// -> (root) for malloc
// -> <inherit> _get_argv_one
__attribute__((nonnull(1)))
char	**build_cmd(t_cmdelmarr *elemarr, char *const *envp, int exit_stat)
{
	int			argc;
	char		**argv;
	int			i_argv;
	size_t		i_elemarr;

	if (!set_var_values(elemarr, envp, exit_stat)
		|| !validate_red_fname(elemarr) || !set_wildcard_values(elemarr)
		|| !elems_make_flat(elemarr))
		return (NULL);
	argc = _get_argc(elemarr);
	if (argc <= 0)
	{
		errstr_ret_false("build_cmd()/_get_argc()", "too many args");
		return (NULL);
	}
	argv = (char **)malloc(sizeof(char **) * ((size_t)argc + 1));
	if (argv == NULL)
		return ((void *)(strerr_ret_false("build_cmd()/malloc") * 0UL));
	argv[argc] = NULL;
	i_argv = 0;
	i_elemarr = 0;
	while (i_argv < argc)
		argv[i_argv++] = _get_argv_one(elemarr, &i_elemarr);
	return (argv);
}
