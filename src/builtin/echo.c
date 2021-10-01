/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 14:13:19 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

int	echo(const char *path, char *const argv[], char *const envp[])
{
	int	idx;
	int	flag;

	g_exit_code = EXIT_SUCCESS;
	flag = 1;
	idx = 0;
	if (!argv[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (g_exit_code);
	}
	if (!ft_strcmp(argv[1], "-n"))
		flag = 2;
	while (argv[idx + flag])
	{
		ft_putstr_fd(argv[flag + idx++], STDOUT_FILENO);
		if (argv[idx + flag])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag != 2)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (g_exit_code);
}
