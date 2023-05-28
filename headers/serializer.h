/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:01:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 01:10:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_H
# define SERIALIZER_H

# include "ft_vect/ft_vect.h"

typedef t_vect	t_cmdarr;
typedef t_vect	t_cmdelmarr;

// NORMAL	: 通常のコマンド部分。変数展開等は特に行わない
// VARIABLE	: 変数展開を行う必要がある部分。
// RED_*	: リダイレクトに関連する情報が格納されている部分
typedef enum e_cmd_elem_type
{
	CMDTYP_NORMAL,
	CMDTYP_VARIABLE,
	CMDTYP_QUOTE_VAR,
	CMDTYP_RED_IN,
	CMDTYP_RED_HEREDOC,
	CMDTYP_RED_OUT,
	CMDTYP_RED_APPEND,
	CMDTYP_PIPE,
	CMDTYP_RED_HEREDOC_SAVED,
}	t_cmd_elem_type;

// type		: その範囲が担う役割
// elem_top	: その範囲の先頭
// len		: その範囲の長さ
// nospace	: VARIABLEおよびその前のNORMALにて、スペースが無い場合 = 次と連結する必要がある
typedef struct s_cmd_elem
{
	t_cmd_elem_type	type;
	const char		*elem_top;
	size_t			len;
	bool			nospace;
}	t_cmd_elem;

// エラー発生時は、メッセージを出力したうえで (t_vect){0} を返す
// return: t_vect<t_cmdelmarr>
t_cmdarr	serialize(const char *input)
			__attribute__((nonnull));

int			dispose_t_cmdarr(t_cmdarr *cmd);

bool		is_cetyp_redirect(t_cmd_elem_type t);
bool		is_cetyp_var_or_normal(t_cmd_elem_type t);
bool		is_cetyp_terminator(t_cmd_elem_type t);

#endif
