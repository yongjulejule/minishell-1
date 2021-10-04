/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_to_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 14:26:44 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

static int	ft_launch_minishell(char *str, char *envp[])
{
	char	*line_read;
	t_cmds	*cmdlst;
	char	**ft_envp;

	ft_envp = dup_envp(envp, ft_strsetlen(envp));
	reset_env(&ft_envp);
	sh_next_level(&ft_envp);
	if (dup2(STDIN_FILENO, BACKUP_FD) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	sigint_n_sigquit_handler(main_sig_handler);
	line_read = ft_strdup(str);
	unexp_eof_sig_handler();
	eof_exit(line_read);
	parse_line_main(&cmdlst, line_read, ft_strdup(""));
	if (cmdlst && cmdlst->cmd && *cmdlst->cmd)
		exec_cmd_main(cmdlst, &ft_envp);
	sigint_n_sigquit_handler(main_sig_handler);
	free_cmds_lst(&cmdlst);
	free(line_read);
	exit(g_exit_code);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	char	**ft_envp;
	t_cmds	*cmdlst;

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		ft_launch_minishell(argv[2], envp);
	else
	{
		ft_envp = esh_pre_process(argc, argv, envp);
		while (1)
		{
			unexp_eof_sig_handler();
			rl_outstream = stderr;
			line_read = readline("🐘 esh > ");
			eof_exit(line_read);
			add_history(rl_line_buffer);
			parse_line_main(&cmdlst, line_read, ft_strdup(""));
			if (cmdlst && cmdlst->cmd && *cmdlst->cmd)
				exec_cmd_main(cmdlst, &ft_envp);
			sigint_n_sigquit_handler(main_sig_handler);
			free_cmds_lst(&cmdlst);
			free(line_read);
		}
	}
	return (EXIT_SUCCESS);
}
