/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _childs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:56:38 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/08 00:31:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHILDS_H
# define _CHILDS_H

# include <stdnoreturn.h>

# include "childs.h"

# define PID_FORKED (0)

# define PIPEFD_FROM_THIS (1)
# define PIPEFD_TO_THIS (0)
# define PIPEFD_FROM_PREV (PIPEFD_TO_THIS)
# define PIPEFD_TO_NEXT (PIPEFD_FROM_THIS)

noreturn void	exec_command(t_ch_proc_info *info_arr, size_t index);

#endif
