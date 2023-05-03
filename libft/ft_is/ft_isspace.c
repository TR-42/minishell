/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:56:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 13:01:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is.h"

int	ft_isspace(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	return (
		uc == CHAR_HTAB
		|| uc == CHAR_LF
		|| uc == CHAR_VTAB
		|| uc == CHAR_FF
		|| uc == CHAR_CR
		|| uc == CHAR_WS
	);
}
