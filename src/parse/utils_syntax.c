/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:37:22 by ghan              #+#    #+#             */
/*   Updated: 2021/09/24 11:04:09 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_strset(char *str, char **strset)
{
	int	i;

	if (!strset)
		return (0);
	i = 0;
	while (strset[i])
	{
		if (!ft_strcmp(str, strset[i++]))
			return (1);
	}
	return (0);
}

int	is_strset_end(char *str, char **strset)
{
	int	i;
	int	len;
	int	cmp_len;

	if (!strset)
		return (0);
	len = ft_strlen(str);
	i = -1;
	while (strset[++i])
	{
		cmp_len = ft_strlen(strset[i]);
		if (len >= cmp_len && !ft_strcmp(str + len - cmp_len, strset[i]))
			return (1);
	}
	return (0);
}

void	init_symbols(char **symbols)
{
	symbols[0] = ">";
	symbols[1] = "<";
	symbols[2] = ">>";
	symbols[3] = ">>";
	symbols[4] = "&>";
	symbols[5] = "<&";
	symbols[6] = ">&";
	symbols[7] = "<>";
	symbols[8] = "&";
	symbols[9] = "&&";
	symbols[10] = NULL;
}
