/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _validate_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:58:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 22:48:48 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - STDERR_FILENO
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "error_utils.h"

#include "validator.h"

#define E_INVAL_NO_CMD "minishell: no command was found at cmd[%d]\n"
#define E_PIPE_NO_PAIR "minishell: no pipe pair was set with cmd[%d]\n"
#define E_REDIR_NO_ARG "minishell: no redirect arg was set in cmd[%d]\n"
#define E_VALID_UNKNOW "minishell: unknown validation error in cmd[%d]\n"

// returns
// - true: It is valid input -> continue processing
// - false: It is NOT valid input
// !! ERR_PRINTED (バリデーション結果の出力)
// -> `arr`変数自体がinvalidの場合、serializer側でエラー出力済み
__attribute__((nonnull))
bool	_validate_input(t_cmdarr *arr, int *ret)
{
	t_cmd_i_inval	inval;

	*ret = 0;
	if (arr->p == NULL || arr->len <= 0)
	{
		vect_dispose(arr);
		return (false);
	}
	inval = is_valid_input(arr);
	if (inval.type == CMD_INVAL_NO_ERR)
		return (true);
	dispose_t_cmdarr(arr);
	*ret = 1;
	if (inval.type == CMD_INVAL_NOCMD)
		ft_dprintf(STDERR_FILENO, E_INVAL_NO_CMD, (int)(inval.index));
	else if (inval.type == CMD_INVAL_PIPE_NOPAIR)
		ft_dprintf(STDERR_FILENO, E_PIPE_NO_PAIR, (int)(inval.index));
	else if (inval.type == CMD_INVAL_REDIRECT_NOARG)
		ft_dprintf(STDERR_FILENO, E_REDIR_NO_ARG, (int)(inval.index));
	else
		ft_dprintf(STDERR_FILENO, E_VALID_UNKNOW, (int)(inval.index));
	return (false);
}
