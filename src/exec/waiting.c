/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:09:06 by jun               #+#    #+#             */
/*   Updated: 2021/09/30 15:29:02 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_exit_code;

int	get_exit_status(int status)
{
	int	exit_code;

	if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	else if (wifexited(status))
		exit_code = wexitstatus(status);
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
	g_exit_code = exit_code;
}
