/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:34 by ghan              #+#    #+#             */
/*   Updated: 2021/09/09 12:08:34 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
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

	envp = 0;
	if (argc > 1 || argv[1])
		is_error(NULL, NULL, "esh does not receive arguments", EXIT_FAILURE);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line_read = readline("🐘 esh > ");
		if (!line_read)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(rl_line_buffer);
		free(line_read);
	}
	return (EXIT_SUCCESS);
}
