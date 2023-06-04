/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _build_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:41:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 18:17:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUILD_CMD_H
# define _BUILD_CMD_H

# include "serializer.h"

int		_get_argc(const t_cmdelmarr *elmarr)
		__attribute__((nonnull));

size_t	_one_elem_count(const t_cmdelmarr *elemarr, size_t i_start)
		__attribute__((nonnull));

char	*_get_argv_one(const t_cmdelmarr *elemarr, size_t *i_start)
		__attribute__((nonnull(1, 2)));

char	**build_cmd(t_cmdelmarr *elemarr, char *const *envp, int exit_stat)
		__attribute__((nonnull(1)));

bool	set_var_values(t_cmdelmarr *elemarr, char *const *envp, int exit_stat)
		__attribute__((nonnull));

char	**ft_split_fp(char const *s, int (*is_spc)(int))
		__attribute__((nonnull));

bool	vect_insert_range(t_vect *vect, size_t index, void *d, size_t len)
		__attribute__((nonnull(1)));

bool	elems_make_flat(t_cmdelmarr *elemarr)
		__attribute__((nonnull));

bool	set_wildcard_values(
			t_cmdelmarr *elemarr
			)
		__attribute__((nonnull));

#endif
