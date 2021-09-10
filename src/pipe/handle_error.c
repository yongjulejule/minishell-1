/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:09:26 by jun               #+#    #+#             */
/*   Updated: 2021/09/10 16:20:24 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	is_error(char *str_1, char *str_2, int exit_status)
{
	if (str_1 != NULL)
		ft_putstr_fd(str_1, 2);
	if (str_2 != NULL)
		ft_putstr_fd(str_2, 2);
	write(2, "\n", 1);
	exit(exit_status);
}
