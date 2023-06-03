/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrnullempty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 02:59:49 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 03:00:09 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_filectrl_tools.h"

bool	ft_isstrnullempty(const char *str)
{
	return (str == NULL || *str == '\0');
}
