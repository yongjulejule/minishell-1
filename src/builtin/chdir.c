/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:43:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/24 11:19:58 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static	int	is_error_no_exit(char *str1, char *str2, char *err_msg, int status)
{
	if (!str1)
		ft_putstr_fd(str1, STDERR_FILENO);
	if (!str2)
		ft_putstr_fd(str2, STDERR_FILENO);
	if (!err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

static	int	handle_exit_error(char *cmd, char *argument)
{
	int	exit_status;

	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	exit_status = is_error_no_exit(": ", argument,
			strerror(errno), EXIT_FAILURE);
	return (exit_status);
}

void	cd(const char *path, char *const argv[], char *const envp[])
{
	char	*home;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (!argv[1])
	{
		home = ft_strdup(getenv("HOME"));
		if (!home)
			home = ft_strdup(".");
		if (chdir(home) == -1)
			exit_status = handle_exit_error((char *)path, home);
		/* TODO : setting PWD env */
		//		else
		//			update_env("PWD", home);
		free(home);
		home = NULL;
	}
	if (chdir(argv[1]) == -1)
		exit_status = handle_exit_error((char *)path, argv[1]);
	/* TODO : setting PWD env as absolate path */
	//	else
	//		update_env("PWD", argv[1]);
	g_exit_code = exit_status;
}
