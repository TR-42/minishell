/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _build_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:41:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 20:48:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUILD_CMD_H
# define _BUILD_CMD_H

# include "serializer.h"

int		_get_argc(const t_cmdelmarr *elmarr);
size_t	_one_elem_count(const t_cmdelmarr *elemarr, size_t i_start);

char	**build_cmd(t_cmdelmarr *elemarr, const char **envp);

#endif
