/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:33:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/10 11:57:29 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - SIGQUIT / SIGINT etc.
#include <signal.h>

#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "error_utils.h"

static const char	*_get_sig_str(int sig)
{
	if (sig == SIGSEGV)
		return ("SIGSEGV");
	else if (sig == SIGSYS)
		return ("SIGSYS");
	else if (sig == SIGPIPE)
		return ("SIGPIPE");
	else if (sig == SIGALRM)
		return ("SIGALRM");
	else if (sig == SIGTERM)
		return ("SIGTERM");
	else if (sig == SIGURG)
		return ("SIGURG");
	else if (sig == SIGSTOP)
		return ("SIGSTOP");
	else if (sig == SIGTSTP)
		return ("STGTSTP");
	else if (sig == SIGCONT)
		return ("SIGCONT");
	else if (sig == SIGCHLD)
		return ("SIGCHLD");
	else if (sig == SIGTTIN)
		return ("SIGTTIN");
	else if (sig == SIGTTOU)
		return ("SIGTTOU");
	return ("!! UNKNOWN SIGNAL !!");
}

bool	print_sig_ret_false(pid_t pid, int sig)
{
	const char	*sigstr;

	if (sig == SIGHUP)
		sigstr = "SIGHUP";
	else if (sig == SIGINT)
		sigstr = "SIGINT";
	else if (sig == SIGQUIT)
		sigstr = "SIGQUIT";
	else if (sig == SIGILL)
		sigstr = "SIGILL";
	else if (sig == SIGTRAP)
		sigstr = "SIGTRAP";
	else if (sig == SIGABRT)
		sigstr = "SIGABRT";
	else if (sig == SIGFPE)
		sigstr = "SIGFPE";
	else if (sig == SIGKILL)
		sigstr = "SIGKILL";
	else if (sig == SIGBUS)
		sigstr = "SIGBUS";
	else
		sigstr = _get_sig_str(sig);
	return (ft_dprintf(STDERR_FILENO, "minishell: [%d]: %s (%d)\n",
			pid, sigstr, sig));
}
