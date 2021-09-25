/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/25 20:09:01 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	t_cmds	*cmdlst;

	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not \
receive arguments", EXIT_FAILURE);
	ft_putendl_fd(ESH_ASCII, STDOUT_FILENO);
	sigint_n_sigquit_handler(main_sig_handler);
	while (1)
	{
		unexp_eof_sig_handler();
		line_read = readline("🐘 esh > ");
		eof_exit(line_read);
		add_history(rl_line_buffer);
		cmdlst = parse_line_main(line_read);
		if (cmdlst && cmdlst->cmd && *cmdlst->cmd)
			exec_cmd_main(cmdlst, envp);
		sigint_n_sigquit_handler(main_sig_handler);
		free_cmds_lst(&cmdlst);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
