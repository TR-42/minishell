/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 01:07:52 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/09 00:15:51 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);

// argument type is different with original `vprintf`
// ref: https://stackoverflow.com/questions/8047362
int	ft_vprintf(const char *format, va_list *args);
int	ft_vdprintf(int fd, const char *format, va_list *args);

#endif
