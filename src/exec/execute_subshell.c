/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 23:55:44 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		args->cmd[idx].exec_f.exec(args->cmd[idx].params[0],
				args->cmd[idx].params, args->envp);
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

static void	processing_subshell(t_args *args, int idx)
{
	pid_t		pid;

	if (args->cnt != idx && args->cnt > 1)
		if (pipe(args->cmd[idx].pipe_fd) == -1)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	if (args->cmd[idx].params && args->cmd[idx].params[0]
		&& !ft_strcmp(args->cmd[idx].params[0], "./minishell"))
		sigint_n_sigquit_handler(multi_shell_erase_newline);
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
		processing_subshell(args, ++idx);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}

void	execute_subshell_main(t_args *args)
{
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		processing_subshell(args, 0);
	else if (pid > 0)
	{
		sigint_n_sigquit_handler(ignore_signal);
		signal(SIGUSR1, SIG_IGN);
		waitpid(pid, &status, 0);
		if (wifexited(status))
			g_exit_code = wexitstatus(status);
		else
			g_exit_code = EXIT_FAILURE;
		return ;
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}
