/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:54:32 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 18:39:55 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _EXEC_BUILTIN_H
# define _EXEC_BUILTIN_H

int	builtin_cd(char **argv);
int	builtin_echo(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv, int status);
int	builtin_export(char **argv);
int	builtin_pwd(char **argv);
int	builtin_unset(char **argv);

#endif