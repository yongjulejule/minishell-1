/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iserror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:35:29 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/09 14:35:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	is_error(char *str_1, char *str_2, int exit_status)
{
	if (str_1 != NULL)
		ft_putstr_fd(str_1, 2);
	if (str_2 != NULL)
		ft_putstr_fd(str_2, 2);
	write(2, "\n", 1);
	exit(exit_status);
}
