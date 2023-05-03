/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:39:01 by kfujita           #+#    #+#             */
/*   Updated: 2023/03/02 11:23:50 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

// Dependency:
// - size_t
# include <stddef.h>

// Libft-00
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// Libft-02 (Libc functions)
void	*ft_calloc(size_t count, size_t size);

// orig
void	*ft_calloc_nofill(size_t count, size_t size);

void	ft_swap(void *a, void *b, size_t bytes);

#endif