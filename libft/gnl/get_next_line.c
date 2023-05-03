/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:17:29 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/07 01:00:36 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../ft_mem/ft_mem.h"
#include "../ft_vect/ft_vect.h"

// - read
#include <unistd.h>

// - ssize_t
#include <sys/types.h>

// - free
#include <stdlib.h>

static const t_gnl_state	g_gnl_state_init_val = {
	// fd
	0,
	// buf
	NULL,
	// len
	0,
	// cap
	0
};

t_gnl_state	gen_gnl_state(int fd, ssize_t cap)
{
	t_gnl_state	state;

	state = g_gnl_state_init_val;
	state.buf = ft_calloc(cap, sizeof(char));
	if (state.buf != NULL)
		state.cap = cap;
	state.fd = fd;
	return (state);
}

void	dispose_gnl_state(t_gnl_state *state)
{
	free(state->buf);
	*state = g_gnl_state_init_val;
}

// `\n` found: TRUE
//  not found: FALSE
static bool	check_and_update_state(t_vect *ret, t_gnl_state *state)
{
	char	*lf_ptr;
	size_t	append_len;

	if (state->len == 0)
		return (false);
	lf_ptr = (char *)ft_memchr(state->buf, '\n', state->len);
	if (lf_ptr == NULL)
		append_len = state->len;
	else
		append_len = lf_ptr - state->buf + 1;
	vect_append_str(ret, state->buf, append_len);
	if (lf_ptr != NULL)
	{
		ft_memmove(state->buf, state->buf + append_len,
			state->len - append_len);
		state->len -= append_len;
	}
	else
		state->len = 0;
	return (lf_ptr != NULL);
}

char	*get_next_line(t_gnl_state *state)
{
	t_vect	ret;
	ssize_t	read_result;

	if (state == NULL || state->buf == NULL || state->cap == 0)
		return (NULL);
	ret = vect_init(0, sizeof(char));
	if (check_and_update_state(&ret, state))
		return (ret.p);
	while (true)
	{
		read_result = read(state->fd, state->buf, state->cap);
		if (read_result <= 0)
		{
			dispose_gnl_state(state);
			if (ret.len == 0)
				vect_dispose(&ret);
			return (ret.p);
		}
		state->len = read_result;
		if (check_and_update_state(&ret, state))
			return (ret.p);
	}
}
