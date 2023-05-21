/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sig_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:02:15 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 23:18:56 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - sigaction
// - sigemptyset
#include <signal.h>

// - perror
#include <stdio.h>

// - write
// - STDOUT_FILENO
#include <unistd.h>

// - rl_event_hook
// - rl_done
#include <readline/readline.h>

#include "signal_handling.h"

static volatile sig_atomic_t	g_is_interrupted = false;

inline bool	get_is_interrupted(void)
{
	return (g_is_interrupted == true);
}

// SIGINT: Ctrl-C
static void	_sig_handler(int sig_no)
{
	if (sig_no != SIGINT)
		return ;
	g_is_interrupted = true;
}

// ref: http://ogawa.s18.xrea.com/tdiary/20080319p02.html
static int	_rl_ev_hook_handler(void)
{
	if (!g_is_interrupted)
		return (0);
	rl_event_hook = NULL;
	rl_done = true;
	return (0);
}

// rl_catch_signals ref:
//   https://docs.rtems.org/releases/4.5.1-pre3/toolsdoc/gdb-5.0-docs/readline/
//     readline00030.html
bool	init_sig_handler(void)
{
	struct sigaction	action;
	struct sigaction	action_sigquit;

	action.sa_handler = _sig_handler;
	action.sa_flags = 0;
	if (sigemptyset(&action.sa_mask) != 0)
	{
		perror("minishell: signal handler init");
		return (false);
	}
	action_sigquit = action;
	action_sigquit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &action, NULL) != 0
		|| sigaction(SIGQUIT, &action_sigquit, NULL) != 0)
	{
		perror("minishell: register signal handler");
		return (false);
	}
	rl_catch_signals = 0;
	g_is_interrupted = false;
	return (true);
}

void	register_rl_ev_hook_handler(void)
{
	if (g_is_interrupted)
		write(STDOUT_FILENO, "\n", 1);
	g_is_interrupted = false;
	rl_event_hook = _rl_ev_hook_handler;
}
