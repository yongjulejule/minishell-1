/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/02 16:01:47 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	echo_value(char *const argv[], int *idx, int flag)
{
	while (argv[*idx + flag])
	{
		ft_putstr_fd(argv[flag + (*idx)++], STDOUT_FILENO);
		if (argv[*idx + flag])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	echo(const char *path, char *const argv[], char *const envp[])
{
	int	idx;
	int	flag;

	if (!path || !argv || !envp)
	{
		g_exit_code = is_error_no_exit("export : ", NULL,
				"pass valid args to builtin functions", EXIT_FAILURE);
		return (g_exit_code);
	}
	g_exit_code = EXIT_SUCCESS;
	flag = 1;
	idx = 0;
	if (!argv[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (g_exit_code);
	}
	while (!ft_strcmp(argv[flag], "-n"))
		flag++;
	echo_value(argv, &idx, flag);
	if (flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (g_exit_code);
}
