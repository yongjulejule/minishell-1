/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/27 16:30:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	cd_check_error(char *cmd, char *arg)
{
	char	*tmp;

	tmp = NULL;
	if (chdir(arg) == -1)
	{
		if (arg && *arg)
		{
			tmp = ft_strjoin(arg, ": ");
			g_exit_code = is_error_no_exit("cd: ", tmp,
					strerror(errno), EXIT_FAILURE);
			free(tmp);
		}
		else
			g_exit_code = is_error_no_exit("cd: ", arg,
					strerror(errno), EXIT_FAILURE);
	}
	// else
	// 	update_pwd("PWD", home);
}

int	cd(const char *path, char *const argv[], char ***const envp)
{
	char	*home;

	g_exit_code = EXIT_SUCCESS;
	if (!argv[1])
	{
		home = ft_get_envp(*envp, "HOME");
		if (!home)
			g_exit_code = is_error_no_exit("cd: ", NULL,
					"HOME not set", EXIT_FAILURE);
		else
			cd_check_error((char *)path, home);
	}
	else
		cd_check_error((char *)path, argv[1]);
	return (g_exit_code);
}
