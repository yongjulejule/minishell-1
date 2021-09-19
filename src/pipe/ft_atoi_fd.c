/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 08:52:00 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/19 08:55:21 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_atoi_fd(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					cnt;

	sign = 1;
	num = 0;
	cnt = 10;
	str = go_to_digit((char *)str, &sign);
	while (*str >= '0' && *str <= '9' && --cnt)
		num = 10 * num + (*str++ - '0');
	if (num > 2147483647 || !cnt)
	{
		if (sign == -1 && num == 2147483648)
			return (sign * num);
		else 
			return (-1);
	}
	return (sign * num);
}
