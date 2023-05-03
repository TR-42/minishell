/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:01:55 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 13:00:12 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_H
# define FT_IS_H

# define CHAR_HTAB '\t'
# define CHAR_LF '\n'
# define CHAR_VTAB '\v'
# define CHAR_FF '\f'
# define CHAR_CR '\r'
# define CHAR_WS ' '

// Libft-00
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

// Additional Functions (from libc)
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isspace(int c);

#endif
