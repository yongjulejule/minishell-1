/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:16:22 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 17:11:44 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*go_to_digit(char *str, int *sign)
{
	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	if (*str == '-')
	{
		str++;
		*sign = -1;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					cnt;

	sign = 1;
	num = 0;
	cnt = 20;
	str = go_to_digit((char *)str, &sign);
	while (*str >= '0' && *str <= '9' && --cnt)
		num = 10 * num + (*str++ - '0');
	if (num > 9223372036854775807 || !cnt)
	{
		if (sign == 1)
			return (-1);
		else if (sign == -1 && num != 9223372036854775808ULL)
			return (0);
		cnt--;
	}
	return (sign * num);
}
