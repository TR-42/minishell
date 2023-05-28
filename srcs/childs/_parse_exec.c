/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:57:28 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 23:04:27 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

#include "childs.h"

#include "validator.h"

// !! ERR_PRINTED
// -> <inherit> serialize
// -> <inherit> _validate_input (バリデーション結果の出力)
// -> <inherit> chk_do_heredoc
// -> <inherit> init_ch_proc_info_arr
__attribute__((nonnull))
int	_parse_exec(const char *str, char *const envp[])
{
	t_cmdarr		arr;
	t_cprocinf		*cparr;
	int				cpstat;

	if (*str == '\0')
		return (0);
	arr = serialize(str);
	if (!_validate_input(&arr, &cpstat))
		return (cpstat);
	if (!chk_do_heredoc(&arr, envp))
		return (dispose_t_cmdarr(&arr) + 1);
	cparr = init_ch_proc_info_arr(&arr, (char **)envp);
	cpstat = 1;
	if (cparr != NULL)
		cpstat = _exec_ch_proc_info_arr(cparr, arr.len);
	rm_tmpfile(&arr);
	dispose_t_cmdarr(&arr);
	dispose_proc_info_arr(cparr);
	return (cpstat);
}
