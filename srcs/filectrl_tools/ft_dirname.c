/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 23:42:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 00:03:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string/ft_string.h"

#include "_filectrl_tools.h"

/**
 * @brief 与えられたパスの、ディレクトリを表す部分を返す
 * 
 * @param path ディレクトリを取得したいパス
 * @return char* 最後のスラッシュを含まない、ディレクトリを表す文字列
 * (但し、`/`のみが渡された場合は、ルートディレクトリとして`/`を返す)
 * @warning 戻り値はmallocされた領域です
 */
char	*ft_dirname(const char *path)
{
	char	*pos;

	if (path == NULL)
		return (ft_strdup("."));
	pos = ft_strrchr(path, '/');
	if (pos == NULL)
		return (ft_strdup("."));
	else if (path == pos)
		return (ft_strdup("/"));
	return (ft_strndup(path, pos - path));
}
