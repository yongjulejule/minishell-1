/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:22:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/20 16:45:00 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	sigint_n_sigquit_handler(void (*sigfunction))
{
	signal(SIGINT, sigfunction);
	signal(SIGQUIT, sigfunction);
}

void	signal_handle_wo_rl_prompt(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	return ;
}

void	reset_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		signal(sig, (void (*)(int))0);
	}
}

void	signal_exit(int signal)
{
	signal += 128;
	exit(signal);
}
