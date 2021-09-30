/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 16:57:28 by ghan             ###   ########.fr       */
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
		printf("\n");
		return (g_exit_code);
	}
	if (!ft_strcmp(argv[1], "-n"))
		flag = 2;
	while (argv[idx + flag])
		printf("%s", argv[flag + idx++]);
	if (flag != 2)
		printf("\n");
	return (g_exit_code);
}
