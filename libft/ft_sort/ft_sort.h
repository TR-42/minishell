/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:48:34 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/19 00:43:17 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

// - size_t
# include <stddef.h>

// - bool
# include <stdbool.h>

typedef int	(*t_compar)(const void *, const void *);

bool	ft_qsort(void *base, size_t nmemb, size_t memb_size, t_compar compar);

#endif
