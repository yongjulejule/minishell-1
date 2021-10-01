/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:37:33 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 21:56:39 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	**esh_pre_process(int argc, char *argv[], char *envp[])
{
	char	**ret;

	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not \
	receive arguments", EXIT_FAILURE);
	ret = dup_envp(envp, ft_strsetlen(envp));
	reset_env(&ret);
	sh_next_level(&ret);
	if (dup2(STDIN_FILENO, BACKUP_FD) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	ft_putendl_fd(ESH_ASCII, STDOUT_FILENO);
	sigint_n_sigquit_handler(main_sig_handler);
	return (ret);
}

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
