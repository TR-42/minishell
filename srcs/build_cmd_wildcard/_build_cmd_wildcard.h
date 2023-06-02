/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _build_cmd_wildcard.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:07:44 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 00:19:41 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUILD_CMD_WILDCARD_H
# define _BUILD_CMD_WILDCARD_H

# include "serializer.h"

bool	_contains_valid_wildcard(
			t_cmd_elem *elems,
			size_t i_start,
			size_t i_next
			)
		__attribute__((nonnull));

char	*get_left_path(
			t_cmd_elem *elems,
			size_t i_wildcard
			)
		__attribute__((nonnull));

#endif
