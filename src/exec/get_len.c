/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:14:57 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 13:22:48 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	get_wspace_len(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;
	int	flag;

	flag = 0b0000;
	idx = 0;
	cnt = 0;
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
		cnt++;
	}
	return (cnt);
}

int	get_quote_len(char *str, char *charset, char ign)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
	while (!is_charset(*(str + idx), charset) && str[idx] != '\0')
	{
		if (ign != '\0' && is_charset(*(str + idx + 1), "\"\\$"))
			idx += 2;
		else
			idx++;
		cnt++;
	}
	return (cnt);
}
