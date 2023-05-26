/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_ch_proc_info_arr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:55:33 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 23:11:44 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - waitpid
#include <sys/wait.h>

// - EXIT_SUCCESS
#include <stdlib.h>

#include "ft_printf/ft_printf.h"

#include "childs.h"

int	_exec_ch_proc_info_arr(t_cprocinf *cparr, size_t cparr_len)
{
	int		cpstat;
	size_t	i_exec;
	size_t	i_wait;

	i_exec = 0;
	i_wait = 0;
	cpstat = 0;
	while (i_exec < cparr_len)
		pipe_fork_exec(cparr, i_exec++, cparr_len);
	close(cparr->fd_stdin_save);
	close(cparr->fd_stdout_save);
	while (i_wait < i_exec)
		waitpid(cparr[i_wait++].pid, &cpstat, 0);
	if (WIFEXITED(cpstat))
		return (WEXITSTATUS(cpstat));
	else
		return (130);
}
