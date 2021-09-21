/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breed_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/21 10:40:40 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

extern int	g_exit_code;

static void	execute_pipe_cmd(t_args *args, int idx)
{
	if (args->cnt > idx + 1)
		connect_pipe_fd(args->cmd[idx].pipe_fd, STDOUT_FILENO);
	if (idx > 0)
		connect_pipe_fd(args->cmd[idx - 1].pipe_fd, STDIN_FILENO);
	redirect_stream(&args->cmd[idx]);
	if (args->cmd[idx].params && args->cmd[idx].params[0])
	{
		sigint_n_sigquit_handler(reset_signal);
		execve(args->cmd[idx].params[0], args->cmd[idx].params, args->envp);
	}
	else
		exit(EXIT_SUCCESS);
	if (errno == E_ACCESS)
		is_error(NULL, "permission denied: ", args->cmd[idx].params[0], X_ERR);
	else if (errno == E_NOCMD || args->cmd[idx].params[0] == NULL)
		is_error(NULL, "command not found: ",
			args->cmd[idx].params[0], CMD_ERR);
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}

static void	execute_processes(t_args *args, int idx)
{
	pid_t		pid;

	if (args->cnt != idx && args->cnt > 1)
		if (pipe(args->cmd[idx].pipe_fd) == -1)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	pid = fork();
	args->cmd[idx].pid = pid;
	if (pid == 0)
		execute_pipe_cmd(args, idx);
	else if (pid > 0)
	{
		if (args->cnt > 1 && idx > 0)
			destroy_pipe(args->cmd[idx - 1].pipe_fd);
		if (args->cnt - 1 == idx)
			wait_process(args);
		execute_processes(args, ++idx);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}

void	breed_process(t_args *args)
{
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		execute_processes(args, 0);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (wifexited(status))
			g_exit_code = wexitstatus(status);
		else
			g_exit_code = EXIT_SUCCESS;
		exit(g_exit_code);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}
