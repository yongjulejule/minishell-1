/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 20:30:26 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

int	env(const char *path, char *const argv[], char *const envp[])
{
	int	idx;

	if (!path || !argv || !envp)
	{
		g_exit_code = is_error_no_exit("export : ", NULL,
				"pass valid args to builtin functions", EXIT_FAILURE);
		return (g_exit_code);
	}
	g_exit_code = EXIT_SUCCESS;
	if (argv[1])
	{
		is_error_no_exit("env : ", argv[1],
			": env in minishell takes no arguments or options", EXIT_FAILURE);
		g_exit_code = EXIT_FAILURE;
	}
	else
	{
		idx = -1;
		while (envp[++idx])
		{
			if (ft_strchr(envp[idx], '='))
				printf("%s\n", envp[idx]);
		}
	}
	return (g_exit_code);
}
