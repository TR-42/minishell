/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:07:31 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 21:47:44 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <stdbool.h>

bool	get_is_interrupted(void);
bool	init_sig_handler(void);
void	register_rl_ev_hook_handler(void);
bool	restore_sig_handler(void);

#endif
