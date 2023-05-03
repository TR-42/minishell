/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:28:26 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/06 23:57:54 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECT_H
# define FT_VECT_H

# include <stddef.h>
# include <stdbool.h>

# ifndef FT_VECT_EXPAND_STEP
#  define FT_VECT_EXPAND_STEP 32
# endif

typedef struct s_vect
{
	size_t	cap;
	size_t	len;
	size_t	elemsize;
	void	*p;
}	t_vect;

t_vect	vect_init(size_t cap, size_t elemsize);

bool	vect_reserve(t_vect *vect, size_t newcap);

void	*vect_at(const t_vect *vect, size_t index);

bool	vect_append_str(t_vect *vect, const char *value, size_t count);
bool	vect_append_range(t_vect *vect, const void *value, size_t count);

bool	vect_push_back(t_vect *vect, const void *elem, size_t *written_index);

bool	vect_set(t_vect *vect, const void *elem, size_t index);

bool	vect_remove(t_vect *vect, size_t index);

void	vect_dispose(t_vect *vect);
void	vect_dispose_each(t_vect *vect, void (*disposer)(void *));
void	vect_dispose_ptrarr(t_vect *vect);

#endif
