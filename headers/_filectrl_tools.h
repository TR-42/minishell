/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _filectrl_tools.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:16:23 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/16 23:09:31 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FILECTRL_TOOLS_H
# define _FILECTRL_TOOLS_H

// - bool
# include <stdbool.h>

# define CHK_GET_PATH_ERR_OK (0)
# define CHK_GET_PATH_ERR_NOFILE (1)
# define CHK_GET_PATH_ERR_NOCMD (2)

typedef struct s_wcinfo
{
	const char	*left_dir;
	const char	*left_fname;
	const char	*right_fname;
	const char	*right_path;
}	t_wcinfo;

bool	chk_and_get_fpath(
			const char *given_path, char **dst, char **envp)
		__attribute__((nonnull(2)));

char	*join_path(const char *path1, const char *path2)
		__attribute__((nonnull));

char	*ft_dirname(const char *path);
char	*ft_basename(const char *path);

bool	vect_append_ptr(t_vect *vect, const void *elem)
		__attribute__((nonnull));

char	*gen_path_str(
			const char *ldir,
			const char *fname,
			const char *rdir
			);

bool	ft_isstrnullempty(const char *str);

/**
 * @brief 指定のディレクトリから指定の条件に合致するファイルを探索する
 * 
 * @param left_dir 上位ディレクトリ (指定しない場合は、`NULL` or `.`)
 * @param left_fname 左のファイル名条件 (指定しない場合は`NULL`)
 * @param right_fname 右のファイル名条件 (指定しない場合は`NULL`)
 * @param right_dir 下位ディレクトリ (指定しない場合は、`NULL`)
 * @return char** 検索結果となるファイル一覧 (存在しなかった場合は空の配列、NULLはERR)
 */
char	**search_files(
			const char *left_dir,
			const char *left_fname,
			const char *right_fname,
			const char *right_dir
			);

#endif
