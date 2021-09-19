/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:09:06 by jun               #+#    #+#             */
/*   Updated: 2021/09/19 17:39:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	get_exit_status(int status)
{
	int	exit_code;

	if (wifexited(status))
		exit_code = wexitstatus(status);
	else if (wifsignaled(status))
		exit_code = wtermsig(status);
	else
		exit_code = EXIT_FAILURE;
	return (exit_code);
}

void	wait_process(t_args *args)
{
	int		status;
	int		exit_code;
	int		cmd;
	pid_t	execed_pid;

	execed_pid = 0;
	while (execed_pid != -1)
	{
		cmd = 0;
		while (cmd < args->cnt)
		{
			execed_pid = wait(&status);
			if (execed_pid == args->cmd[args->cnt - 1].pid)
				exit_code = get_exit_status(status);
			cmd++;
		}
	}
	exit(exit_code);
}
