/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_idx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:50:30 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/02 13:51:01 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_quote_idx(char *str, char *charset, char ign)
{
	int	idx;

	idx = 0;
	if (!str || !*str)
		return (0);
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (*(str + idx) == ign)
		{
			idx++;
			if (*(str + idx) == ign)
				idx++;
		}
		else
			idx++;
	}
	return (idx);
}

static int	update_flag(char *str, int flag)
{
	if (*(str) == '\'' && flag != 0b010)
	{
		if (!flag)
			flag = 0b100;
		else
			flag = 0;
	}
	else if (*(str) == '\"' && flag != 0b100)
	{
		if (!flag)
			flag = 0b010;
		else
			flag = 0;
	}
	return (flag);
}

int	get_wspace_idx(char *str, char *charset, char ign)
{
	int	idx;
	int	flag;

	flag = 0b0000;
	idx = 0;
	if (!str || !*str)
		return (0);
	while (flag || (!is_charset(*(str + idx), charset) && str[idx] != '\0'))
	{
		if (*(str + idx) == ign)
			idx += 2;
		else
		{
			flag = update_flag(str + idx, flag);
			idx++;
		}
	}
	return (idx);
}
