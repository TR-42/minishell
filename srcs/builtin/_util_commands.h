/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _util_commands.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:04:47 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 18:56:49 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTIL_COMMANDS_H
# define _UTIL_COMMANDS_H

# include <stdlib.h>

# define MANYARGERR "too many arguments"
# define FEWARGERR "too few arguments"
# define PRINTFERR "an error happened in printf"
# define INVALIDERR "not a valid identifier"
# define NOTNUMERR "numeric argument required"

size_t	get_strslen(char **src);
void	free_all(char **dst);
int		print_error(char *command, char *name, char *message, int err);
size_t	ft_putstr_fd_with_err(char *s, int fd);

#endif