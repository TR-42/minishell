/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:02:37 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 00:34:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

// - bool
# include <stdbool.h>

# include "serializer.h"

typedef enum e_cmd_inval_typ
{
	CMD_INVAL_NO_ERR,
	CMD_INVAL_NOCMD,
	CMD_INVAL_OP_NOPAIR,
	CMD_INVAL_REDIRECT_NOARG,
	CMD_INVAL_TOO_MANY_WILDCARD,
}	t_cmd_inval_typ;

typedef struct s_cmd_i_inval
{
	size_t			index;
	t_cmd_inval_typ	type;
}	t_cmd_i_inval;

bool			_validate_input(t_cmdarr *arr, int *ret)
				__attribute__((nonnull));

t_cmd_i_inval	is_valid_input(const t_cmdarr *cmdarr)
				__attribute__((nonnull));
t_cmd_inval_typ	is_valid_cmd(const t_cmdelmarr *cmdelemarr, bool is_last_cmd)
				__attribute__((nonnull));

bool			validate_red_fname(const t_cmdelmarr *elemarr)
				__attribute__((nonnull(1)));

#endif
