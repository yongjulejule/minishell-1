/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:22:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 11:23:06 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	signal_handle_wo_rl_prompt(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	return ;
}

void	signal_exit(int signal)
{
	exit(signal);
}

