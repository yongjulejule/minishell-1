/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:01:16 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/03 13:37:48 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_ll	check_exit_arg_validity(char **argv)
{
	t_ll	status;
	size_t	idx;
	size_t	sign;

	idx = 0;
	sign = 0;
	if (is_charset(argv[1][idx], "+-"))
		sign = 1;
	while (ft_isdigit(argv[1][idx + sign]))
		idx++;
	if ((idx > 19 + sign) || argv[1][idx + sign] != '\0')
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		is_error(argv[1], ": ", "numeric argument required", 255);
	}
	status = ft_atol(argv[1]);
	if (ft_strlen(argv[1]) == (19 + sign) && (status == 0 || status == -1))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		is_error(argv[1], ": ", "numeric argument required", 255);
	}
	return (status);
}

int	ext(const char *path, char *const argv[], char *const envp[])
{
	extern int	g_exit_code;

	if (!path || !argv || !envp)
	{
		g_exit_code = is_error_no_exit("export : ", NULL,
				"pass valid args to builtin functions", EXIT_FAILURE);
		return (g_exit_code);
	}
	if (!argv[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(g_exit_code);
	}
	if (ft_strsetlen((char **)argv) > 2)
	{
		check_exit_arg_validity((char **)argv);
		ft_putendl_fd("exit\n🤣 esh: exit : too many arguments", STDERR_FILENO);
		g_exit_code = 1;
		return (-1);
	}
	exit(check_exit_arg_validity((char **)argv) & (0xff));
}
