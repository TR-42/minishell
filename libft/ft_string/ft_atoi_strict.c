/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:16:40 by kfujita           #+#    #+#             */
/*   Updated: 2023/03/02 11:20:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_is/ft_is.h"
#include "../ft_math/ft_math.h"

// - NULL
#include <stddef.h>

static bool	set_value(char c, int *value, int sign)
{
	int	c_value;

	if (!ft_isdigit(c))
		return (false);
	c_value = (c - '0') * sign;
	if (!can_mul(*value, 10) || !can_add(*value * 10, c_value))
		return (false);
	*value = (*value * 10) + c_value;
	return (true);
}

bool	ft_atoi_strict(const char *str, const char **endptr, int *dst)
{
	int	sign;

	if (str == NULL || dst == NULL)
		return (false);
	if (*endptr != NULL)
		*endptr = str;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (*endptr != NULL)
		*endptr = str;
	if (!ft_isdigit(*str))
		return (false);
	*dst = 0;
	while (set_value(*str, dst, sign))
		str++;
	if (*endptr != NULL)
		*endptr = str;
	return (true);
}
