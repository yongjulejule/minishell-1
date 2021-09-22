/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/09/22 16:38:03 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(char **cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
}

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
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
