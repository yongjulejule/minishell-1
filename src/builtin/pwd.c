/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:24:54 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 16:48:45 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

int	pwd(const char *path, char *const argv[], char *const envp[])
{
	if (argv[1])
	{
		if (argv[1][0] == '-')
		{
			g_exit_code = is_error_no_exit("pwd: ",
					argv[1], ": ", EXIT_FAILURE);
			ft_putendl_fd("pwd: no option support in esh", STDERR_FILENO);
		}
	}
	else
	{
		printf("%s\n", getenv("PWD"));
		g_exit_code = EXIT_SUCCESS;
	}
	return (g_exit_code);
}
