/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:32:50 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/05 16:35:34 by ghan             ###   ########.fr       */
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

static void	error_before_execve(t_args *args, int idx)
{
	struct stat	mode;
	char		*tmp;

	if (!args->cmd[idx].params)
		exit(EXIT_SUCCESS);
	if (!ft_strcmp(args->cmd[idx].params[0], "."))
		is_error(NULL, args->cmd[idx].params[0], " : command not found",
			CMD_ERR);
	tmp = ft_get_envp(args->envp, "PATH");
	if (tmp && *tmp && !ft_strchr(args->cmd[idx].params[0], '/'))
		is_error(args->cmd[idx].params[0], ": ", "command not found", CMD_ERR);
	stat(args->cmd[idx].params[0], &mode);
	if (s_isdir(mode.st_mode))
		is_error(args->cmd[idx].params[0], ": ", "is a directory", X_ERR);
}

static void	error_after_execve(t_args *args, int idx)
{
	if (args->cmd[idx].builtin != notbuiltin)
		exit(g_exit_code);
	if (errno == EACCES)
		is_error(args->cmd[idx].params[0], " :", strerror(errno), X_ERR);
	else if (errno == ENOENT || args->cmd[idx].params[0] == NULL)
	{
		if (!ft_get_envp(args->envp, "PATH"))
			is_error(args->cmd[idx].params[0], " :", strerror(errno), CMD_ERR);
		else
			is_error(args->cmd[idx].params[0], " :",
				"command not found", CMD_ERR);
	}
	else if (errno == ENOEXEC)
		is_error(NULL, NULL, strerror(errno), 2);
	else
		is_error(args->cmd[idx].params[0], " :", strerror(errno), EXIT_FAILURE);
}

static void	execute_pipe_cmd(t_args *args, int idx)
{
	t_builtin	builtin;

	builtin = args->cmd[idx].builtin;
	connect_pipestream(args, idx);
	if (redirect_stream(&args->cmd[idx]))
		exit(g_exit_code);
	if (builtin == notbuiltin)
		error_before_execve(args, idx);
	sigint_n_sigquit_handler(reset_signal);
	if (builtin == is_ext)
		delete_output();
	if (builtin == is_cd || builtin == is_exprt || builtin == is_unset)
		args->cmd[idx].exec_f.exec_env(args->cmd[idx].params[0],
				args->cmd[idx].params, &args->envp);
	else
		args->cmd[idx].exec_f.exec(args->cmd[idx].params[0],
				args->cmd[idx].params, args->envp);
	error_after_execve(args, idx);
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
