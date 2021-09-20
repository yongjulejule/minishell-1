/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/20 14:30:59 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

extern int g_exit_code;

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
	pid_t		pid;
	int			status;
	static int	cmd_start;

	sigint_n_sigquit_handler((signal_handle_wo_rl_prompt));
	if (cmds[cmd_end][0] == ';' || !cmds[cmd_end + 1])
	{
		pid = fork();
		if (pid < 0)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
		else if (pid == 0)
		{
			sigint_n_sigquit_handler(signal_exit);
			process_to_execute(cmds, envp, *cmd_cnt, cmd_start);
		}
		waitpid(pid, &status, 0);
		g_exit_code = wexitstatus(status); 
		fprintf(stderr, "%d\n", g_exit_code);
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

	cmd_end = 0;
	cmd_cnt = 1;
	while (cmds[cmd_end])
	{
		seperate_cmd(cmds, envp, cmd_end, &cmd_cnt);
		cmd_end++;
	}
	return (EXIT_SUCCESS);
}
