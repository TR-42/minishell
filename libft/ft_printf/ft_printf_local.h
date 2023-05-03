/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_local.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:04:40 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 17:12:07 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_LOCAL_H
# define FT_PRINTF_LOCAL_H

# include <stddef.h>
# include <stdbool.h>
# include <stdarg.h>
# include "../ft_lst/ft_lst.h"

// 2 + 16 + 1
# define STR_BUF_LEN (19)

typedef unsigned char	t_uint8;

typedef enum e_dtype
{
	STR,
	CHAR,
	PTR,
	INT_10BASE,
	UINT_10BASE,
	UINT_16BASE,
}	t_dtype;

typedef union u_data
{
	char			str_buf[STR_BUF_LEN];
	char			*str;
	void			*p_ptr;
	size_t			ptr;
	char			c;
	int				s_digit;
	unsigned int	u_digit;
}	t_data;

typedef struct s_printf_fmt
{
	t_dtype	type;
	t_data	data;
	char	header[3];
	t_uint8	head_len;
	int		str_len;
	int		min_len;
	int		max_len;

	bool	f_upper:	1;
	bool	f_minus:	1;
	bool	f_zero:		1;
	bool	f_dot:		1;
	bool	f_hash:		1;
	bool	f_space:	1;
	bool	f_plus:		1;
}	t_fmt;

t_list	*parse_format(const char *fmt, va_list *args);

t_fmt	*parse_opt(size_t *len, char **fmt, va_list *args);
t_fmt	*check_no_opt_str(size_t *len, char **fmt, t_fmt *p_ret);

void	parse_opt_flags(char **fmt, t_fmt *p_ret);
bool	parse_opt_c_str(char fmt, va_list *args, t_fmt *p_ret);
bool	parse_opt_num(char fmt, va_list *args, t_fmt *p_ret);
bool	parse_opt_ptr(char fmt, va_list *args, t_fmt *p_ret);

bool	is_valid_conv_char(char c);
bool	is_valid_flag_char(char c);

int		print_all(int fd, t_list *list);

#endif
