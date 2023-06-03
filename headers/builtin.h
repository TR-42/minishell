/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:37:32 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 19:39:33 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>

char	**get_environs(void);
bool	init_environs(char **envs);
void	dispose_environs(void);

int		exec_builtin(char **argv, int *exit_status);
bool	is_builtin(char **argv);

#endif