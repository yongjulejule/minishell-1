/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/22 16:36:46 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

extern int	g_exit_code;

static void	process_to_execute(char **cmds, char **envp,
		int cmd_cnt, int cmd_start)
{
	t_args	*args;

	args = (t_args *)ft_calloc(1, sizeof(t_args));
	args->envp = envp;
	args->cnt = cmd_cnt;
	args->cmd = (t_cmd *)ft_calloc(args->cnt + 1, sizeof(t_cmd));
	build_structure(&cmds[cmd_start], envp, args);
	breed_process(args);
}

static void	seperate_cmd(char **cmds, char **envp, int cmd_end, int *cmd_cnt)
{
	static int	cmd_start;

	if (cmds[cmd_end][0] == ';' || !cmds[cmd_end + 1])
	{
		process_to_execute(cmds, envp, *cmd_cnt, cmd_start);
		cmd_start = cmd_end + 1;
		*cmd_cnt = 1;
	}
	else if (cmds[cmd_end][0] == '|')
		*cmd_cnt += 1;
	if (!cmds[cmd_end + 1])
		cmd_start = 0;
}

int	exec_cmd_main(char **cmds, char **envp)
{
	int		cmd_end;
	int		cmd_cnt;

	sigint_n_sigquit_handler(signal_handle_wo_rl_prompt);
	cmd_end = 0;
	cmd_cnt = 1;
	while (cmds[cmd_end])
	{
		seperate_cmd(cmds, envp, cmd_end, &cmd_cnt);
		cmd_end++;
	}
	return (EXIT_SUCCESS);
}
