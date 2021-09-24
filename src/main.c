/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/24 15:19:32 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	t_cmds	*cmds_hd;

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
		cmds_hd = parse_line_main(line_read);
		// if (cmds_hd->next && cmds_hd->next->cmd && *(cmds_hd->next->cmd))
		// 	exec_cmd_main(cmds_hd, envp);
		envp = 0;
		sigint_n_sigquit_handler(main_sig_handler);
		free_cmds_lst(&cmds_hd);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
