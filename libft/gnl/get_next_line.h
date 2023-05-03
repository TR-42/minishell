/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:15:58 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/07 01:00:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// - bool
# include <stdbool.h>

// - ssize_t
# include <sys/types.h>

typedef struct s_gnl_state
{
	int		fd;
	char	*buf;
	ssize_t	len;
	ssize_t	cap;
}	t_gnl_state;

t_gnl_state	gen_gnl_state(int fd, ssize_t cap);

void		dispose_gnl_state(t_gnl_state *state);

char		*get_next_line(t_gnl_state *state);

#endif
