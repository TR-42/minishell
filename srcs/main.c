/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/17 23:16:52 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - exit
#include <stdlib.h>

// - STDERR_FILENO
#include <unistd.h>

#include "ft_string/ft_string.h"
#include "ft_printf/ft_printf.h"

#include "childs.h"
#include "serializer.h"
#include "validator.h"

#define E_OPT_LESS_ARG "%s: %s: option requires an argument\n"
#define E_INVAL_NO_CMD "minishell: no command was found at cmd[%d]\n"
#define E_PIPE_NO_PAIR "minishell: no pipe pair was set with cmd[%d]\n"
#define E_REDIR_NO_ARG "minishell: no redirect arg was set in cmd[%d]\n"
#define E_VALID_UNKNOW "minishell: unknown validation error in cmd[%d]\n"

static int	_validate_input(t_cmdarr *arr)
{
	t_cmd_i_inval	inval;

	inval = is_valid_input(arr);
	if (inval.type == CMD_INVAL_NO_ERR)
		return (0);
	dispose_t_cmdarr(arr);
	if (inval.type == CMD_INVAL_NOCMD)
		ft_dprintf(STDERR_FILENO, E_INVAL_NO_CMD, (int)(inval.index));
	else if (inval.type == CMD_INVAL_PIPE_NOPAIR)
		ft_dprintf(STDERR_FILENO, E_PIPE_NO_PAIR, (int)(inval.index));
	else if (inval.type == CMD_INVAL_REDIRECT_NOARG)
		ft_dprintf(STDERR_FILENO, E_REDIR_NO_ARG, (int)(inval.index));
	else
		ft_dprintf(STDERR_FILENO, E_VALID_UNKNOW, (int)(inval.index));
	return (1);
}

// TODO: serialize後のバリデーション/エラー処理
// TODO: init_ch_...後のエラー処理
static int	_parse_exec(const char *str, const char *envp[])
{
	t_cmdarr		arr;
	t_cprocinf		*cparr;
	size_t			i;
	int				cpstat;

	arr = serialize(str);
	cpstat = _validate_input(&arr);
	if (cpstat != 0)
		return (cpstat);
	cparr = init_ch_proc_info_arr(&arr, (char **)envp);
	i = 0;
	while (i < arr.len)
	{
		pipe_fork_exec(cparr, i, arr.len);
		i++;
	}
	i = 0;
	while (i < arr.len)
		waitpid(cparr[i++].pid, &cpstat, 0);
	dispose_proc_info_arr(cparr);
	if (WIFEXITED(cpstat))
		return (WEXITSTATUS(cpstat));
	else
		return (130);
}

static void	_chk_do_c_opt(int argc, const char *argv[], const char *envp[])
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

int	main(int argc, const char *argv[], const char *envp[])
{
	_chk_do_c_opt(argc, argv, envp);
	return (0);
}
