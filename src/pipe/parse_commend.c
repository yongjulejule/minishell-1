/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 13:36:00 by jun               #+#    #+#             */
/*   Updated: 2021/09/11 10:15:57 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	allocate_pipe_memory(t_args *args)
{
	int	cnt;

	cnt = 0;
	args->pipe_fd = (int **)ft_calloc(args->argc - 4, sizeof(int *));
	while (cnt < args->argc - 4)
	{
		args->pipe_fd[cnt] = (int *)ft_calloc(2, sizeof(int));
		cnt++;
	}
}

static void	init_pipe_structure(t_args *args)
{
	if (!ft_memcmp(argv[1], "here_doc", ft_strlen("here_doc") + 1))
	{
		if (argc < 6)
			is_error("pipex: ", "check arguments in heredoc", EXIT_FAILURE);
		args->is_heredoc = 1;
		args->limiter = argv[2];
		args->file[0] = ft_strdup(".tmp.here_doc");
		if (!(args->file[0]))
			is_error("pipex: ", "error in malloc", EXIT_FAILURE);
	}
	else
	{
		args->is_heredoc = 0;
		args->file[0] = argv[1];
	}
	args->file[1] = argv[argc - 1];
	args->params = (char ***)ft_calloc(argc - 2, sizeof(char **));
	args->params[argc - 2 - 1] = NULL;
	args->argc = argc;
	args->pid = (pid_t *)ft_calloc(argc - 3, sizeof(pid_t));
}

void	make_cmds(t_args *args)
{
	int	cmd_idx;

	cmd_idx = 0;
	while (args->params[cmd_idx] != NULL)
	{
		check_cmd_validity(args, cmd_idx, args->params[cmd_idx][0]);
		cmd_idx++;
	}
}

static void	init_structure(char **cmds, t_args *args)
{
	int	cnt;
}

void	build_structure(char **cmds, char **envp, t_args *args)
{
	extern int	errno;

	init_structure(cmds, args);
	init_pipe_structure(args);
	args->env_path = getenv("PATH");
	args->envp = envp;
	if (!args->env_path)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	get_params(argv, args);
	make_cmds(args);
	if (args->is_heredoc)
		args->argc--;
	allocate_pipe_memory(args);
}
