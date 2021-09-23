/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/23 09:11:45 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	char	**cmds;

	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not receive arguments", EXIT_FAILURE);
	sigint_n_sigquit_handler(main_sig_handler);
	while (1)
	{
		line_read = readline("🐘 esh > ");
		if (!line_read || !ft_strncmp(line_read, "exit", 4))
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(rl_line_buffer);
		cmds = parse_line_main(line_read);
		if (cmds && *cmds && **cmds)
			exec_cmd_main(cmds, envp);
		sigint_n_sigquit_handler(main_sig_handler);
		free_cmds(cmds);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
