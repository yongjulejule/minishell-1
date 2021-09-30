/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:22:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 14:18:47 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	signal_handle_wo_rl_prompt(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		write(STDOUT_FILENO, "\n", 1);
}

void	reset_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		signal(sig, SIG_DFL);
}

void	multi_shell_erase_newline(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ignore_signal(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		signal(sig, SIG_IGN);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	no_newline_for_sigquit(int sig)
{
	if (sig == SIGUSR1)
		signal(SIGQUIT, SIG_IGN);
}
