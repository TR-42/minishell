/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _environ.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:07:19 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 18:36:59 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENVIRON_H
# define _ENVIRON_H

# include <stdbool.h>
# include <string.h>

# define SETENVERR "failed to set an environ"
# define RMENVERR "failed to remove an environ"

char	***get_saved_environs(void);
bool	set_environ(char *src);
bool	remove_environ(char *name);
char	**search_environ(const char *name);

#endif