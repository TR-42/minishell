/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 23:01:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - exit
// (for debug)
// - getenv
// - system
#include <stdlib.h>

// (for debug)
// - getpid
#include <unistd.h>

// (for debug)
// - sprintf
#include <stdio.h>

// - readline etc.
#include <readline/readline.h>
#include <readline/history.h>

#include "ft_string/ft_string.h"

#include "childs.h"
#include "builtin.h"
#include "error_utils.h"
#include "serializer.h"
#include "signal_handling.h"

#define PROMPT_STR "minishell> "

#define E_OPT_LESS_ARG "%s: %s: \n"

// !! ERR_PRINTED
// -> (root) too few args
// -> <inherit> _parse_exec
__attribute__((nonnull))
static void	_chk_do_c_opt(int argc, const char *argv[])
{
	if (argc < 2 || ft_strncmp(argv[1], "-c", 3) != 0)
		return ;
	if (argc == 2)
	{
		errstr_ret_false(argv[1], "option requires an argument");
		exit(2);
	}
	exit(_parse_exec(argv[2]));
}

static int	do_loop(void)
{
	char	*line;
	int		ret;

	ret = 0;
	while (true)
	{
		register_rl_ev_hook_handler();
		line = readline(PROMPT_STR);
		if (get_is_interrupted())
			ret = 1;
		else if (line == NULL)
			return (ret);
		else if (*line != '\0')
		{
			add_history(line);
			ret = _parse_exec(line);
		}
		free(line);
		rl_on_new_line();
	}
	return (ret);
}

int	main(int argc, const char *argv[], char **envp)
{
	int		ret;

	if (!init_environs(envp))
	{
		errstr_ret_false("init_environs()", "malloc failed");
		return (1);
	}
	_chk_do_c_opt(argc, argv);
	if (!init_sig_handler())
		return (1);
	ret = do_loop();
	dispose_environs();
	return (ret);
}

#if DEBUG

# define DEBUG_LEAKS_CMD_LEN (32)

__attribute__((destructor))
static void	destructor(void) {
	char	cmd[DEBUG_LEAKS_CMD_LEN];

	if (getenv("DEBUG") == NULL)
		return ;
	snprintf(cmd, DEBUG_LEAKS_CMD_LEN, "leaks %d", getpid());
	system(cmd);
}

#endif
