/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 20:58:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

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

// - fstat
#include <sys/stat.h>

// - readline etc.
#include <readline/readline.h>
#include <readline/history.h>

#include "ft_string/ft_string.h"
#include "gnl/get_next_line.h"

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
static bool	_chk_do_c_opt(int argc, const char *argv[], int *ret)
{
	if (argc < 2 || ft_strncmp(argv[1], "-c", 3) != 0)
		return (false);
	if (argc == 2)
	{
		*ret = 2;
		return (!errstr_ret_false(argv[1], "option requires an argument"));
	}
	*ret = _parse_exec(argv[2], 0);
	return (true);
}

// ref: https://syohex.hatenablog.com/entry/20130302/1362190989
// !! ERR_PRINTED
// -> (root) for fstat (エラーが出ても処理は続行する)
// -> (root) for gen_gnl_state / malloc (エラーが出たらプログラム終了)
// -> (root) for get_next_line / malloc (エラーが出たらプログラム終了)
static bool	_chk_do_script(int *ret)
{
	struct stat	st;
	t_gnl_state	gnl;
	char		*line;

	if (fstat(STDIN_FILENO, &st) != 0)
		return (strerr_ret_false("_chk_do_script()/fstat"));
	if (!(S_ISFIFO(st.st_mode) || S_ISREG(st.st_mode)))
		return (false);
	gnl = gen_gnl_state(STDIN_FILENO, 256);
	while (gnl.buf != NULL)
	{
		errno = 0;
		line = get_next_line(&gnl);
		if (line == NULL)
			break ;
		*ret = _parse_exec(line, *ret);
		free(line);
	}
	if (errno != 0)
	{
		*ret = 1;
		strerr_ret_false("_chk_do_script()");
	}
	dispose_gnl_state(&gnl);
	return (true);
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
			ret = _parse_exec(line, ret);
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
	if (_chk_do_c_opt(argc, argv, &ret)
		|| _chk_do_script(&ret)
		|| !init_sig_handler())
	{
		dispose_environs();
		return (ret);
	}
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
