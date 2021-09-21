/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:34:39 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/22 00:28:28 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			idx;

	idx = 0;
	if (s1 == s2)
		return (0);
	while (*(s1 + idx) == *(s2 + idx))
	{
		if (*(s1 + idx) == 0 || *(s2 + idx) == 0)
			break ;
		idx++;
	}
	if ((unsigned char)*(s1 + idx) > (unsigned char)*(s2 + idx))
		return (1);
	else if ((unsigned char)*(s1 + idx) < (unsigned char)*(s2 + idx))
		return (-1);
	else
		return (0);
}
