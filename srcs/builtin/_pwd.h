/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 08:31:10 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/11 08:31:10 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PWD_H
# define _PWD_H

# include <stdbool.h>

void	dispose_pwd(void);
bool	update_pwd(bool is_use_env);
char	*get_pwd(void);

#endif