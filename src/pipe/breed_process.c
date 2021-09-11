/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breed_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 19:10:38 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	execute_pipe_cmd(t_args *args, int cmd)
{
	extern int	errno;

	if (args->cmd[cmd].rdr_to)
		rdr_stdout_to_file(args->cmd[cmd].file[1], &args->cmd[cmd]);
	else if (args->cnt > cmd + 1)
		connect_pipe_fd(args->cmd[cmd].pipe_fd, STDOUT_FILENO);
	if (args->cmd[cmd].rdr_from)
		rdr_file_to_stdin(args->cmd[cmd].file[0], &args->cmd[cmd]);
	else if (cmd > 0)
		connect_pipe_fd(args->cmd[cmd - 1].pipe_fd, STDIN_FILENO);
	execve(args->cmd[cmd].params[0], args->cmd[cmd].params, args->envp);
	if (errno == E_ACCESS || args->cmd[cmd].params[0] == NULL)
		is_error(NULL, "permission denied: ", args->cmd[cmd].params[0], X_ERR);
	else if (errno == E_NOCMD)
		is_error(NULL, "command not found: ", args->cmd[cmd].params[0], CMD_ERR);
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}

static void	execute_processes(t_args *args, int cmd)
{
	pid_t		pid;
	extern int	errno;

	if (args->cnt != cmd && args->cnt > 1)
		if (pipe(args->cmd[cmd].pipe_fd) == -1)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	pid = fork();
	args->cmd[cmd].pid = pid;
	if (pid == 0)
		execute_pipe_cmd(args, cmd);
	else if (pid > 0)
	{
		if (cmd > 0 && args->cnt > 1)
			destroy_pipe(args->cmd[cmd - 1].pipe_fd);
		if (args->cnt - 1 == cmd)
			wait_process(args);
		execute_processes(args, ++cmd);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}

void	breed_process(t_args *args)
{
	int			status;
	pid_t		pid;
	extern int	errno;

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
