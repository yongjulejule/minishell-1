/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_qm_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:36:13 by ghan              #+#    #+#             */
/*   Updated: 2021/10/09 16:48:22 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	cnt_prev_bs(char *s, int prev)
{
	while (prev > 0 && s[prev] == '\\')
		prev--;
	return (prev);
}

static size_t	inner_quote_add_bs(char *s, int	*cp_flag, int fst, char cmp)
{
	size_t	add;

	add = 0;
	if (s[fst] == cmp)
	{
		add++;
		cp_flag[fst] = ADD_BS;
	}
	return (add);
}

static size_t	add_cnt_dq(char *s, int *cp_flag, int fst, int len)
{
	size_t	add;

	add = 0;
	while (fst < len)
	{
		if (s[fst] == '\\' && s[fst + 1] == '\n')
		{
			cp_flag[fst] = RM_CHAR;
			cp_flag[fst + 1] = 0;
			fst += 2;
		}
		else if (s[fst] == '\\' && !is_charset(s[fst + 1], "\"\\$"))
		{
			add++;
			if ((fst - cnt_prev_bs(s, fst)) % 2)
				cp_flag[fst] = ADD_BS;
			else
				cp_flag[fst + 1] = ADD_BS;
			fst += 2;
		}
		else if (s[fst])
			add += inner_quote_add_bs(s, cp_flag, fst++, '\'');
	}
	return (add);
}

static size_t	add_cnt_sq(char *s, int *cp_flag, int fst, int len)
{
	size_t	add;

	add = 0;
	while (fst < len)
	{
		if (s[fst] == '\\')
		{
			add++;
			cp_flag[fst] = ADD_BS;
			fst++;
		}
		else if (s[fst])
			add += inner_quote_add_bs(s, cp_flag, fst++, '"');
	}
	return (add);
}

size_t	flag_add_cnt(char *s, int *cp_flag, int fst, int len)
{
	size_t	add;
	int		k;

	k = fst - 1;
	add = 0;
	while (++k < len)
	{
		if (is_charset(s[k], " \n\t"))
		{
			add++;
			cp_flag[k] = ADD_BS;
		}
	}
	if (s[fst - 1] == '"')
		add += add_cnt_dq(s, cp_flag, fst, len);
	else if (s[fst - 1] == '\'')
		add += add_cnt_sq(s, cp_flag, fst, len);
	return (add);
}
