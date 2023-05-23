/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:02:37 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 15:58:49 by kfujita          ###   ########.fr       */
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
	CMD_INVAL_PIPE_NOPAIR,
	CMD_INVAL_REDIRECT_NOARG,
}	t_cmd_inval_typ;

typedef struct s_cmd_i_inval
{
	size_t			index;
	t_cmd_inval_typ	type;
}	t_cmd_i_inval;

bool			_validate_input(t_cmdarr *arr, int *ret);

t_cmd_i_inval	is_valid_input(const t_cmdarr *cmdarr);
t_cmd_inval_typ	is_valid_cmd(const t_cmdelmarr *cmdelemarr, bool is_last_cmd);

#endif
