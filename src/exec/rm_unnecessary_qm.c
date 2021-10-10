/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unnecessary_qm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/10/10 21:33:02 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	consecutive_empty_qm(char *str, int i)
{
	char	prev;
	int		k;

	prev = str[i - 1];
	k = i - 2;
	while (k >= 1
		&& (!ft_strncmp(str + k, "\"\"", 2) || !ft_strncmp(str + k, "''", 2)))
	{
		prev = str[k - 1];
		k -= 2;
	}
	if (!ft_strncmp(str + i, "\"\"", 2) || !ft_strncmp(str + i, "''", 2))
		i += 2;
	if ((is_charset(prev, " \n\t") && !str[i])
		|| ((prev == -1 || (is_charset(prev, " \n\t")))
			&& is_charset(str[i], " \n\t")))
		return (1);
	return (0);
}

static size_t	flag_cp_char(char *str, int *cp_flag)
{
	int		i;
	size_t	add_cnt;

	add_cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (is_charset(str[i], "\"'"))
		{
			if (consecutive_empty_qm(str, i))
				i += 2;
			if (is_charset(str[i], "\"'"))
			{
				flag_qm(str, &i, cp_flag, &add_cnt);
				i++;
			}
		}
		else if (str[i])
			i++;
	}
	return (add_cnt);
}

void	rm_unnecessary_qm(char **param)
{
	int		*cp_flag;
	size_t	add_cnt;
	size_t	len;

	len = ft_strlen(*param);
	cp_flag = (int *)ft_calloc(len, sizeof(int));
	add_cnt = flag_cp_char(*param, cp_flag);
	rm_or_expand_qm(param, cp_flag, len, add_cnt);
	free(cp_flag);
}
