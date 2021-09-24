/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 11:26:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/24 11:32:51 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_error_no_exit(char *str1, char *str2, char *err_msg, int status)
{
	ft_putstr_fd("🤣 esh: ", STDERR_FILENO);
	if (!str1)
		ft_putstr_fd(str1, STDERR_FILENO);
	if (!str2)
		ft_putstr_fd(str2, STDERR_FILENO);
	if (!err_msg)
		ft_putstr_fd(err_msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

