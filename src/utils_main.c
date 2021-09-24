/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/09/24 10:58:03 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	free_cmds_lst(t_cmds **cmds_hd)
{
	t_cmds	*elem;

	elem = *cmds_hd;
	while (elem)
	{
		free(elem->cmd);
		elem = elem->next;
		free(*cmds_hd);
		*cmds_hd = elem;
	}
	*cmds_hd = NULL;
}

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_code = 1;
	}
	else if (signal == SIGQUIT)
		rl_on_new_line();
	rl_redisplay();
}

void	sigint_n_sigquit_handler(void (*sigfunction))
{
	signal(SIGINT, sigfunction);
	signal(SIGQUIT, sigfunction);
}
