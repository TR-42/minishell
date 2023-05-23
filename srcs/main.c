/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 21:40:18 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - exit
// (for debug)
// - getenv
// - system
#include <stdlib.h>

// - STDERR_FILENO
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
#include "ft_printf/ft_printf.h"

#include "childs.h"
#include "heredoc.h"
#include "serializer.h"
#include "validator.h"

#define PROMPT_STR "minishell> "

#define E_OPT_LESS_ARG "%s: %s: option requires an argument\n"

// TODO: serialize後のバリデーション/エラー処理
// TODO: init_ch_...後のエラー処理
static int	_parse_exec(const char *str, char *const envp[])
{
	t_cmdarr		arr;
	t_cprocinf		*cparr;
	size_t			i;
	int				cpstat;

	if (str == NULL || *str == '\0')
		return (0);
	arr = serialize(str);
	if (!_validate_input(&arr, &cpstat))
		return (cpstat);
	if (!chk_do_heredoc(&arr, envp))
		return (dispose_t_cmdarr(&arr) + 1);
	cparr = init_ch_proc_info_arr(&arr, (char **)envp);
	i = 0;
	while (i < arr.len)
		pipe_fork_exec(cparr, i++, arr.len);
	close(cparr->fd_stdin_save);
	close(cparr->fd_stdout_save);
	i = 0;
	while (i < arr.len)
		waitpid(cparr[i++].pid, &cpstat, 0);
	(void)(rm_tmpfile(&arr) + dispose_t_cmdarr(&arr));
	dispose_proc_info_arr(cparr);
	if (WIFEXITED(cpstat))
		return (WEXITSTATUS(cpstat));
	else
		return (130);
}

static void	_chk_do_c_opt(int argc, const char *argv[], char *const envp[])
{
	if (argc < 2 || ft_strncmp(argv[1], "-c", 3) != 0)
		return ;
	if (argc == 2)
	{
		ft_dprintf(STDERR_FILENO, E_OPT_LESS_ARG, argv[0], argv[1]);
		exit(2);
	}
	exit(_parse_exec(argv[2], envp));
}

int	main(int argc, const char *argv[], char *const envp[])
{
	char	*line;
	int		ret;

	_chk_do_c_opt(argc, argv, envp);
	ret = 0;
	while (true)
	{
		line = readline(PROMPT_STR);
		if (line == NULL)
			return (ret);
		ret = _parse_exec(line, envp);
		if (*line != '\0')
			add_history(line);
		free(line);
		rl_on_new_line();
	}
	return (0);
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
