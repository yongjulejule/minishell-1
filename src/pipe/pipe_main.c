/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/18 11:28:47 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	process_to_execute(char **cmds, char **envp,
		int cmd_cnt, int cmd_start)
{
	t_args *args;

	args = (t_args *)ft_calloc(1, sizeof(t_args));
	args->envp = envp;
	args->cnt = cmd_cnt;
	build_structure(&cmds[cmd_start], envp, args);
	breed_process(args);
}

static void	seperate_cmd(char **cmds, char **envp, int cmd_end, int *cmd_cnt)
{
	pid_t		pid;
	static int	cmd_start;

	signal(SIGINT, signal_handle_wo_rl_prompt);
	signal(SIGQUIT, signal_handle_wo_rl_prompt);
	if (!ft_strncmp(cmds[cmd_end], ";", 2) || !cmds[cmd_end + 1])
	{
		pid = fork();
		if (pid < 0)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
		else if (pid == 0)
		{
			signal(SIGINT, signal_exit);
			signal(SIGQUIT, signal_exit);
			process_to_execute(cmds, envp, *cmd_cnt, cmd_start);
		}
		waitpid(pid, NULL, 0);
		cmd_start = cmd_end + 1;
//		free_structure();
		*cmd_cnt = 1;
	}
	if (!ft_strcmp(cmds[cmd_end], "|"))
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
