/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:23:12 by kfujita           #+#    #+#             */
/*   Updated: 2023/03/02 11:20:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

// Dependency:
// - size_t
# include <stddef.h>

// - bool
# include <stdbool.h>

// Libft-00
size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

// Libft-01
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_atoi(const char *str);
bool	ft_atoi_strict(const char *str, const char **endptr, int *dst);

// Libft-02 (Libc functions)
char	*ft_strdup(const char *s1);

// Libft-02 (Additional functions)
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set);

char	**ft_split(char const *s, char c);

char	*ft_itoa(int n);

// libft-03
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

// Additional Functions (from libc)
long	ft_strtol(const char *str, char **endptr, int base);
char	*ft_strndup(const char *s1, size_t n);
size_t	ft_strnlen(const char *str, size_t max_len);

// Additional Functions (original)
int		get_numstr_base(char *buf, size_t num, int base, bool is_upper);

#endif
