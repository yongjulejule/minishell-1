/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/11 15:53:03 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal == SIGQUIT)
		rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line_read;
	char	*one_line;
	char	**cmds;

	envp = 0;
	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not receive arguments", EXIT_FAILURE);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	one_line = ft_strdup("");
	while (1)
	{
		line_read = readline("🐘 esh > ");
		if (!line_read)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(rl_line_buffer);
		cmds = complete_a_line(&one_line, line_read);
		/* NOTE : Do we need error_code here? */
//		exec_cmd_main(cmds, envp);
		free_cmds(cmds);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
