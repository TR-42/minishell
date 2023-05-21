/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:37:32 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/21 14:37:32 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>

// return pointer of environs
char	***get_environs(void);

bool	builtin_cd(char *arg);
void	builtin_echo(bool is_option_n, char *arg);
void	builtin_env(void);
int		builtin_exit(char *arg);
bool	builtin_export(char **args);
bool	builtin_pwd(void);
bool	builtin_unset(char **args);

#endif