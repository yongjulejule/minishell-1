/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_strset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:48:20 by ghan              #+#    #+#             */
/*   Updated: 2021/09/26 20:52:59 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	bubble_sort_strset(char **strset, int len)
{
	int	i;
	int	k;

	if (!strset || !len)
		return ;
	i = -1;
	while (++i + 1 < len)
	{
		k = i;
		while (++k < len)
		{
			if (ft_strcmp(strset[i], strset[k]) > 0)
				swap_str(&strset[i], &strset[k]);
		}
	}
}
