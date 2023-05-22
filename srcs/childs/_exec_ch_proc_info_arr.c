/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_ch_proc_info_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:55:33 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 09:27:09 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - waitpid
#include <sys/wait.h>

// - EXIT_SUCCESS
#include <stdlib.h>

#include "ft_printf/ft_printf.h"

#include "childs.h"

// !! ERR_PRINTED
// -> <inherit> pipe_fork_exec
// (pipe_fork_execでエラー発生の場合、return 1)
__attribute__((nonnull))
int	_exec_ch_proc_info_arr(t_cprocinf *cparr, size_t cparr_len)
{
	int		cpstat;
	size_t	i_exec;
	size_t	i_wait;
	t_cetyp	cetype;

	i_exec = 0;
	i_wait = 0;
	cpstat = 0;
	while (i_exec < cparr_len)
	{
		cetype = get_cmdterm(cparr[i_exec].cmd);
		pipe_fork_exec(cparr, i_exec++);
		if (cetype == CMDTYP_PIPE)
			continue ;
		while (i_wait < i_exec)
			waitpid(cparr[i_wait++].pid, &cpstat, 0);
		if (!WIFEXITED(cpstat))
			return (130);
		cpstat = WEXITSTATUS(cpstat);
		if ((cetype == CMDTYP_OP_AND && cpstat != EXIT_SUCCESS)
			|| (cetype == CMDTYP_OP_OR && cpstat == EXIT_SUCCESS))
			break ;
	}
	return (cpstat);
}
