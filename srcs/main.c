/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/17 22:57:22 by kfujita          ###   ########.fr       */
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

#define E_OPT_LESS_ARG "%s: %s: option requires an argument\n"

// TODO: serialize後のバリデーション/エラー処理
// TODO: init_ch_...後のエラー処理
static int	_parse_exec(const char *str, const char *envp[])
{
	t_cmdarr	arr;
	t_cprocinf	*cparr;
	size_t		i;
	int			cpstat;

	arr = serialize(str);
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
