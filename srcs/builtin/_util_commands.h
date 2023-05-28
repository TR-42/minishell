/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _util_commands.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:04:47 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/22 02:04:47 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTIL_COMMANDS_H
# define _UTIL_COMMANDS_H

# include <stdlib.h>

#define ARGERR "too many or few arguments"
#define PRINTFERR "an error happened in printf"

size_t	get_strslen(char **src);
void	free_all(char **dst);
int		print_error(char *command, char *name, char *message, int err);

#endif