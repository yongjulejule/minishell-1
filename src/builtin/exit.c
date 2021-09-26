/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:01:16 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 09:51:18 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_exit_arg_validity(char **argv)
{
	int	idx;
	int	status;

	idx = 0;
	while (ft_isdigit(argv[1][idx]))
		idx++;
	if (argv[1][idx] != '\0' || idx > 19)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		is_error(argv[1], ": ", "numeric argument required", 255);
	}
	status = ft_atoi(argv[1]);
	if (ft_strlen(argv[1]) == 19 && (status == 0 || status == -1))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		is_error(argv[1], ": ", "numeric argument required", 255);
	}
	return (status);
}

/*
** NOTE : exit with pipe -> exit after fork.
**	      without pipe -> do not fork and execute exit
*/

int	ext(const char *path, char *const argv[], char *const envp[])
{
	extern int	g_exit_code;

	if (!argv[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (ft_strsetlen((char **)argv) > 1)
	{
		ft_putendl_fd("exit\n 🤣 esh: exit : too many arguments", STDERR_FILENO);
		g_exit_code = 1;
		return (-1);
	}
	exit(check_exit_arg_validity((char **)argv) & (0xff));
}
