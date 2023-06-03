/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_ch_proc_info_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:55:33 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 21:48:07 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - waitpid
#include <sys/wait.h>

// - EXIT_SUCCESS
#include <stdlib.h>

#include "ft_printf/ft_printf.h"
#include "builtin.h"
#include "_env_util.h"
#include "_childs.h"
#include "_build_cmd.h"
#include "utils.h"

// !! NO_ERROR
__attribute__((nonnull))
static bool	_is_end_and_get_stat(int cpstat, t_cetyp cetype, bool is_signaled,
	int *exit_status)
{
	if (cpstat >> 16 != 0)
		return (true);
	if (is_signaled || !WIFEXITED(cpstat))
	{
		*exit_status = 130;
		return (true);
	}
	*exit_status = WEXITSTATUS(cpstat);
	if ((cetype == CMDTYP_OP_AND && *exit_status != EXIT_SUCCESS)
		|| (cetype == CMDTYP_OP_OR && *exit_status == EXIT_SUCCESS))
		return (true);
	return (false);
}

// !! ERR_PRINTED
// -> <inherit> gen_envp
// -> <inherit> build_cmd
// -> <inherit> pipe_fork_exec
__attribute__((nonnull))
static t_cetyp	_exec_until_term(t_cprocinf *cparr, size_t cparr_len,
	size_t *i_exec, int exit_status)
{
	bool	is_pfe_success;
	t_cetyp	cetype;
	bool	is_one_command;
	int		status;

	is_one_command = get_cmdterm(cparr[*i_exec].cmd) != CMDTYP_PIPE;
	while (*i_exec < cparr_len)
	{
		is_pfe_success = false;
		cetype = get_cmdterm(cparr[*i_exec].cmd);
		cparr[*i_exec].envp = gen_envp();
		cparr[*i_exec].argv = build_cmd(cparr[*i_exec].cmd,
				cparr[*i_exec].envp, exit_status);
		if (is_one_command)
			status = _exec_builtin_red(cparr + *i_exec, &exit_status);
		is_pfe_success = ((is_one_command && status != 0)
				|| pipe_fork_exec(cparr, *i_exec, cparr_len));
		free_2darr((void ***)&(cparr[*i_exec].envp));
		free_2darr((void ***)&(cparr[*i_exec].argv));
		*i_exec += 1;
		if (!is_pfe_success || (is_one_command && status < 0))
			return (false);
		if (cetype != CMDTYP_PIPE)
			return (true);
	}
	return (true);
}

// !! ERR_PRINTED
// -> <inherit> _exec_until_term
// (pipe_fork_execでエラー発生の場合、return 130)
__attribute__((nonnull))
int	_exec_ch_proc_info_arr(t_cprocinf *cparr, size_t cparr_len, int exit_stat)
{
	int		cpstat;
	size_t	i_exec;
	size_t	i_wait;
	t_cetyp	cetype;
	bool	is_signaled;

	i_exec = 0;
	i_wait = 0;
	cpstat = 0;
	is_signaled = false;
	while (i_exec < cparr_len)
	{
		is_signaled = !_exec_until_term(cparr, cparr_len, &i_exec, exit_stat);
		while (i_wait < i_exec)
		{
			if (0 < cparr[i_wait++].pid)
				waitpid(cparr[i_wait - 1].pid, &cpstat, 0);
			is_signaled = (is_signaled
					|| (0 < cparr[i_wait - 1].pid && WIFSIGNALED(cpstat)));
		}
		cetype = get_cmdterm(cparr[i_exec - 1].cmd);
		if (_is_end_and_get_stat(cpstat, cetype, is_signaled, &exit_stat))
			break ;
	}
	return (exit_stat);
}
