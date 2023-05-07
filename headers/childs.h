/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:45:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/08 00:35:37 by kfujita          ###   ########.fr       */
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
	char		*line_ptr;
	int			fd_to_this;
	int			fd_from_this;
	pid_t		pid;
	char		**path_arr;
	char		**envp;
}	t_ch_proc_info;

void	dispose_proc_info_arr(t_ch_proc_info *info_arr);

// バリデーション後、そのままの状態で渡す。
// 変数展開等はfork後に子プロセス側で実行する
void	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count);

#endif
