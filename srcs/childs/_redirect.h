/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:03:38 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 01:12:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _REDIRECT_H
# define _REDIRECT_H

# include <stdbool.h>

# include "childs.h"

bool	_proc_redirect(t_ch_proc_info *info)
		__attribute__((nonnull));

#endif
