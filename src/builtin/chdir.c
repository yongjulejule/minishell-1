/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/02 16:44:13 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	update_pwd(char ***envp, char *arg)
{
	char	*cwd;
	char	*argv_p[3];
	char	*to_free;

	argv_p[0] = "export";
	argv_p[1] = ft_strjoin("OLDPWD=", ft_get_envp(*envp, "PWD"));
	argv_p[2] = NULL;
	exprt("export", argv_p, envp);
	free(argv_p[1]);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		to_free = ft_strjoin(ft_get_envp(*envp, "OLDPWD"), "/");
		cwd = ft_strjoin(to_free, arg);
		free(to_free);
		is_error_no_exit("cd: ", "error retrieving current directory: \
getcwd: ", strerror(errno), EXIT_SUCCESS);
	}
	argv_p[1] = ft_strjoin("PWD=", cwd);
	exprt("export", argv_p, envp);
	free(argv_p[1]);
	free(cwd);
}

static void	cd_check_error(char *arg, char ***envp)
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
		update_pwd(envp, arg);
}

int	cd(const char *path, char *const argv[], char ***const envp)
{
	char	*home;

	if (!path || !argv || !envp)
	{
		g_exit_code = is_error_no_exit("export : ", NULL,
				"pass valid args to builtin functions", EXIT_FAILURE);
		return (g_exit_code);
	}
	g_exit_code = EXIT_SUCCESS;
	if (!argv[1])
	{
		home = ft_get_envp(*envp, "HOME");
		if (!home)
			g_exit_code = is_error_no_exit("cd: ", NULL,
					"HOME not set", EXIT_FAILURE);
		else
			cd_check_error(home, (char ***)envp);
	}
	else
		cd_check_error(argv[1], (char ***)envp);
	return (g_exit_code);
}
