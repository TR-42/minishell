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

# include <stdbool.h>
# include <stdlib.h>

size_t	get_strslen(char **src);
bool	free_all(char ***dst);

#endif