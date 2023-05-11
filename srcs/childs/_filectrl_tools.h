/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _filectrl_tools.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:16:23 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/08 00:13:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FILECTRL_TOOLS_H
# define _FILECTRL_TOOLS_H

# define CHK_GET_PATH_ERR_OK (0)
# define CHK_GET_PATH_ERR_NOFILE (1)
# define CHK_GET_PATH_ERR_NOCMD (2)

int	chk_and_get_fpath(
		const char *given_path, const char **env_path, char **dst);

#endif