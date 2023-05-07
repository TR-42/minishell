/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:02:19 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/07 01:06:44 by kfujita          ###   ########.fr       */
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

bool	_is_valid_var_char(char c);

// ダブルクォーテーションまわりの処理を行う。
// return: Elementが終了するかどうか
bool	_serializer_dquote(const char **input, t_pars_mde *mode, t_cmd_elem *v);

// return: Elementが終了するかどうか
bool	_serializer_redirect(const char **input, t_pars_mde *mode,
			t_cmd_elem *v);

// return: Elementが終了するかどうか
bool	_serializer_pipe(const char **input, t_pars_mde *mode, t_cmd_elem *v);

// return: Elementが終了するかどうか
bool	_serializer_squote(const char **input, t_pars_mde *mode, t_cmd_elem *v);

// return: Elementが終了するかどうか
bool	_serializer_var(const char **input, t_pars_mde *mode, t_cmd_elem *v);

#endif
