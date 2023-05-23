/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:58:43 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 14:37:24 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

// - bool
# include <stdbool.h>

# include "serializer.h"

int		create_tmpfile(char *const *envp, char **fname_save);

bool	chk_do_heredoc(t_cmdarr *cmdarr, char *const *envp);

int		rm_tmpfile(t_cmdarr *cmdarr);

#endif
