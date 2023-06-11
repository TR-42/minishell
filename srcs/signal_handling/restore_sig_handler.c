/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_sig_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:11:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/10 11:28:37 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - sigaction
// - sigemptyset
#include <signal.h>

// - NULL
#include <stddef.h>

#include "error_utils.h"
#include "signal_handling.h"

bool	restore_sig_handler(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	action.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &action, NULL) != 0)
		return (strerr_ret_false("restore SIGQUIT handler"));
	if (sigaction(SIGINT, &action, NULL) != 0)
		return (strerr_ret_false("restore SIGINT handler"));
	return (true);
}
