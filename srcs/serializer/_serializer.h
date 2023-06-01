/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:02:19 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/26 23:00:16 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERIALIZER_H
# define _SERIALIZER_H

# include "serializer.h"

typedef enum e_parser_mode
{
	M_NORMAL,
	M_VAR,
	M_SQUOTE,
	M_DQUOTE,
	M_DQUOTE_VAR,
}	t_pars_mde;

bool	_is_valid_var_char(char c, bool is_first);

bool	_is_special_var_chk(const char **input, t_pars_mde *mode,
			t_cmd_elem *v);

// ダブルクォーテーションまわりの処理を行う。
// return: Elementが終了するかどうか
bool	_serializer_dquote(const char **input, t_pars_mde *mode, t_cmd_elem *v)
		__attribute__((nonnull));

// return: Elementが終了するかどうか
bool	_serializer_redirect(const char **input, t_pars_mde *mode,
			t_cmd_elem *v)
		__attribute__((nonnull));

// return: Elementが終了するかどうか
bool	_serializer_pipe(const char **input, t_pars_mde *mode, t_cmd_elem *v)
		__attribute__((nonnull));

// return: Elementが終了するかどうか
bool	_serializer_squote(const char **input, t_pars_mde *mode, t_cmd_elem *v)
		__attribute__((nonnull));

// return: Elementが終了するかどうか
bool	_serializer_var(const char **input, t_pars_mde *mode, t_cmd_elem *v)
		__attribute__((nonnull));

bool	_serializer_term(const char **input, t_pars_mde *mode, t_cmd_elem *v)
		__attribute__((nonnull));

// return: Elementが終了するかどうか
bool	_serializer_wildcard(const char **input, t_pars_mde *mode,
			t_cmd_elem *v)
		__attribute__((nonnull));

#endif
