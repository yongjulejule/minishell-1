/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 12:31:41 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/06 14:22:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

extern int	g_exit_code;

int	rdr_err(char *str_1, char *str_2, char *err_msg, int exit_status)
{
	ft_putstr_fd("🤣 esh: ", STDERR_FILENO);
	if (str_1 != NULL)
		ft_putstr_fd(str_1, STDERR_FILENO);
	if (str_2 != NULL)
		ft_putstr_fd(str_2, STDERR_FILENO);
	if (err_msg != NULL)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	if (exit_status == CUSTOM_ERR)
	{
		exit_status = EXIT_FAILURE;
		free(str_1);
	}
	write(STDERR_FILENO, "\n", 1);
	g_exit_code = exit_status;
	return (EXIT_FAILURE);
}
