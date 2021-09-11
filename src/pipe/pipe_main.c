/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/11 19:15:53 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	exec_cmd_main(char **cmds, char **envp)
{
	int		cmd_end;
	int		cmd_start;
	int		cmd_cnt;
	extern int	errno;
	pid_t	pid;
	t_args	*args;

	cmd_cnt = 1;
	cmd_end = 0;
	cmd_start = 0;
	while (cmds[cmd_end])
	{
		if (!ft_strncmp(cmds[cmd_end], ";", 2) || !cmds[cmd_end + 1])
		{
			pid = fork();
			if (pid < 0)
				is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
			if (pid == 0)
			{
				args = (t_args *)ft_calloc(1, sizeof(t_args));
				args->envp = envp;
				args->cnt = cmd_cnt;
				build_structure(&cmds[cmd_start], envp, args);
//			int cnt = 0 , cnt1 = 0;
//			while (args->cmd[cnt].params)
//			{
//				while (args->cmd[cnt].params[cnt1])
//				{
//					printf("%s\n", args->cmd[cnt].params[cnt1]);
//					cnt1++;
//				}
//				cnt++;
//			}
				breed_process(args);
			}
			waitpid(pid, NULL, 0);
			cmd_start = cmd_end + 1;
//			free_structure();
			cmd_cnt = 1;
		}
		if (!ft_strncmp(cmds[cmd_end], "|", 2))
			cmd_cnt++;
		cmd_end++;
	}
	return (EXIT_SUCCESS);
}
