/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/28 10:43:09 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	update_pwd(char ***envp)
{
	char	*cwd;
	char	*argv[3];

	cwd = getcwd(NULL, 0);
	argv[0] = "export";
	argv[1] = ft_strjoin("PWD=", cwd);
	argv[2] = NULL;
	exprt("export", argv, envp);
	free(cwd);
	free(argv[1]);
}

static void	cd_check_error(char *cmd, char *arg, char ***envp)
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
	else
		update_pwd(envp);
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
			cd_check_error((char *)path, home, (char ***)envp);
	}
	else
		cd_check_error((char *)path, argv[1], (char ***)envp);
	return (g_exit_code);
}
