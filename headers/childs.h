/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 22:21:21 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILDS_H
# define CHILDS_H

// - pid_t
# include <unistd.h>

# include "serializer.h"

typedef struct s_ch_proc_info
{
	t_cmdarr	*cmdarr;
	t_cmdelmarr	*cmd;
	int			fd_stdin_save;
	int			fd_stdout_save;
	int			fd_to_this;
	int			fd_from_this;
	pid_t		pid;
	char		**envp;
	char		**argv;
}	t_ch_proc_info;

typedef t_ch_proc_info	t_cprocinf;

void		dispose_proc_info_arr(t_ch_proc_info *info_arr);

// バリデーション後、そのままの状態で渡す。
// 変数展開等はfork後に子プロセス側で実行する
bool		pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count,
				int exit_status)
			__attribute__((nonnull));

// バリデーション実行後にこの関数を呼ぶ
t_cprocinf	*init_ch_proc_info_arr(t_cmdarr *cmdarr)
			__attribute__((nonnull));

int			_exec_ch_proc_info_arr(t_cprocinf *cparr, size_t cparr_len,
				int exit_stat)
			__attribute__((nonnull));

int			_parse_exec(const char *str, int exit_stat)
			__attribute__((nonnull));

#endif
