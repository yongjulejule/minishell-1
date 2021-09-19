/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breed_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/19 13:53:59 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	execute_pipe_cmd(t_args *args, int idx)
{
	redirect_stream(&args->cmd[idx]);
	if (args->cnt > idx + 1)
		connect_pipe_fd(args->cmd[idx].pipe_fd, STDOUT_FILENO);
	if (idx > 0)
		connect_pipe_fd(args->cmd[idx - 1].pipe_fd, STDIN_FILENO);
	execve(args->cmd[idx].params[0], args->cmd[idx].params, args->envp);
	if (errno == E_ACCESS || args->cmd[idx].params[0] == NULL)
		is_error(NULL, "permission denied: ", args->cmd[idx].params[0], X_ERR);
	else if (errno == E_NOCMD)
		is_error(NULL, "command not found: ", args->cmd[idx].params[0], CMD_ERR);
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
		if (args->cnt > 1)
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
			exit(wexitstatus(status));
		else
			exit(EXIT_FAILURE);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}
