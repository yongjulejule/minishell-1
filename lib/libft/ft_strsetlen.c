/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsetlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 15:24:52 by jun               #+#    #+#             */
/*   Updated: 2021/09/27 03:14:51 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
int	ft_strsetlen(char **strs)
{
	int	cnt;

	cnt = 0;
	if (strs == NULL)
		return (0);
	if (*strs == NULL)
		return (0);
	while (*strs)
	{
		cnt++;
		strs++;
	}
	return (cnt);
}
