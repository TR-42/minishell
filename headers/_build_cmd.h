/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _build_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:41:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 19:40:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUILD_CMD_H
# define _BUILD_CMD_H

# include "serializer.h"

int		_get_argc(const t_cmdelmarr *elmarr)
		__attribute__((nonnull));

size_t	_one_elem_count(const t_cmdelmarr *elemarr, size_t i_start)
		__attribute__((nonnull));

char	*_get_argv_one(const t_cmdelmarr *elemarr, size_t *i_start,
			char *const *envp)
		__attribute__((nonnull(1, 2)));

char	**build_cmd(t_cmdelmarr *elemarr, char *const *envp)
		__attribute__((nonnull(1)));

#endif
