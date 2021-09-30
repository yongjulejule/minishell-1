/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsetlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 15:24:52 by jun               #+#    #+#             */
/*   Updated: 2021/09/30 16:24:39 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsetlen(char **strs)
{
	int	cnt;

	cnt = 0;
	if (strs == NULL)
		return (0);
	if (*strs == NULL)
		return (0);
	while (strs[cnt])
		cnt++;
	return (cnt);
}
