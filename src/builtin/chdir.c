/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/28 10:47:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	update_pwd(char ***envp)
{
	char	*cwd;
	char	*argv_p[3];
	char	*argv_op[3];

	argv_op[0] = "export";
	argv_op[1] = ft_strjoin("OLDPWD=", ft_get_envp(*envp, "PWD"));
	argv_op[2] = NULL;
	exprt("export", argv_op, envp);
	cwd = getcwd(NULL, 0);
	argv_p[0] = "export";
	argv_p[1] = ft_strjoin("PWD=", cwd);
	argv_p[2] = NULL;
	exprt("export", argv_p, envp);
	free(cwd);
	free(argv_p[1]);
	free(argv_op[1]);
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
