/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 13:16:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

extern int	g_exit_code;

static void	delete_output(void)
{
	int	fd;

	fd = open("/dev/null", O_WRONLY);
	if (fd < 0)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	if (dup2(fd, STDERR_FILENO) < 0)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	close(fd);
}

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
		if (args->cmd[idx].builtin == is_ext)
			delete_output();
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

void	execute_subshell_main(t_args *args, int idx)
{
	pid_t	pid;

	if (args->cnt - 1 != idx && args->cnt > 1)
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
		{
			wait_process(args); 
			return ;
		}
		execute_subshell_main(args, ++idx);
	}
	else
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
}