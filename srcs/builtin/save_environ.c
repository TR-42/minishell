/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:09:14 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/22 02:09:14 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	***get_environs(void)
{
	static char	**save_env = NULL;

	return (&save_env);
}
