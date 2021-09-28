/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:24:54 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/28 11:02:23 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

int	pwd(const char *path, char *const argv[], char *const envp[])
{
	g_exit_code = EXIT_SUCCESS;
	if (argv[1])
	{
		if (ft_strlen(argv[1]) > 1 && argv[1][0] == '-')
		{
			g_exit_code = is_error_no_exit("pwd: ",
					argv[1], ": invalid entry", EXIT_FAILURE);
			ft_putendl_fd("pwd: no option support in esh", STDERR_FILENO);
			return (g_exit_code);
		}
	}
	printf("%s\n", ft_get_envp((char **)envp, "PWD"));
	return (g_exit_code);
}
