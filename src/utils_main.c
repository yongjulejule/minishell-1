/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/09/25 17:52:48 by ghan             ###   ########.fr       */
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

void	unexp_eof_sig_handler(void)
{
	if (g_exit_code == UNEXP_EOF_FLAG)
	{
		signal(SIGINT, unexp_eof_sigint_handler);
		g_exit_code = SYNTAX_ERR;
	}
}

void	eof_exit(char *line_read)
{
	if (!line_read)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
}
