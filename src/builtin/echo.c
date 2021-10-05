/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/05 14:41:25 by ghan             ###   ########.fr       */
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

static int	echo_skip_opt(char *const argv[])
{
	int	idx;
	int	cur;

	idx = 1;
	while (!ft_strncmp(argv[idx], "-n", 2))
	{
		cur = 2;
		while (argv[idx][cur] == 'n')
			cur++;
		if (argv[idx][cur])
			return (idx);
		idx++;
	}
	return (idx);
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
	flag = echo_skip_opt(argv);
	echo_value(argv, &idx, flag);
	if (flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (g_exit_code);
}
