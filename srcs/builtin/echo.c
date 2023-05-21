/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:47 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/20 20:53:47 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "stdbool.h"

// TODO: handle envs
void	builtin_echo(bool is_option_n, char *arg)
{
	ft_printf("%s", arg);
	if (!is_option_n)
		ft_printf("\n");
}
