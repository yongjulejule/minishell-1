/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 21:31:30 by ghan              #+#    #+#             */
/*   Updated: 2021/09/18 21:31:31 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	less_or_greater_than(char *s, int *i, char c)
{
	(*i)++;
	if ((c == '<' && is_charset(*(s + *i), "<>"))
		|| (c == '>' && *(s + *i) == '>'))
		(*i)++;
	else if (*(s + *i) == '&')
	{
		(*i)++;
		if (*(s + *i) == '-')
		{
			(*i)++;
			if (*(s + *i) == '<')
			{
				(*i)++;
				if (is_charset(*(s + *i), "<>"))
					(*i)++;
			}
			else if (*(s + *i) == '>')
			{
				(*i)++;
				if (*(s + *i) == '>')
					(*i)++;
			}
		}
	}
}

static void	skip_after_rdr(char *s, int *i)
{
	while (is_charset(*(s + *i), " \t\n"))
		(*i)++;
	while (*(s + *i) && !is_charset(*(s + *i), "\"'`<>&;| \t\n"))
	{
		if (*(s + *i) == '\\')
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\\"`'<>&;|"))
				(*i)++;
		}
		else if (*(s + *i))
			(*i)++;
	}
	skip_qmbt(s, i);
	if (is_charset(*(s + *i), "\"'`"))
		(*i)++;
}

void	check_rdr_size(char *s, int *size, int *i)
{
	if (*(s + *i) == '&' && !is_charset(*(s + *i + 1), "<>"))
	{
		(*i)++;
		return ;
	}
	else if (*(s + *i) == '&' && is_charset(*(s + *i + 1), "<>"))
		(*i) += 2;
	else if (is_charset(*(s + *i), "<>"))
		less_or_greater_than(s, i, *(s + *i));
	*size += 2;
	if (!is_charset(*(s + *i), "<>&")
		|| (*(s + *i) == '&' && !is_charset(*(s + *i + 1), "<>")))
	{
		(*i)++;
		while (is_charset(*(s + *i), " \t\n"))
			(*i)++;
	}
	if (is_charset(*(s + *i), "<>&"))
		check_rdr_size(s, size, i);
	skip_after_rdr(s, i);
	if (*(s + *i) == '\0')
		(*size)--;
}

void	get_rdr_end_idx(char *s, int start, int *i)
{
	int	n_cnt;

	if (*(s + *i) == '&' && !is_charset(*(s + *i + 1), "<>"))
	{
		(*i)++;
		return ;
	}
	n_cnt = 0;
	while (n_cnt + start + 1 < (*i)
		&& ft_isdigit(*(s + *i - n_cnt - 1)))
		n_cnt++;
	if (n_cnt && n_cnt + start + 1 < (*i))
	{
		(*i) -= n_cnt;
		return ;
	}
	if (*(s + *i) == '&' && is_charset(*(s + *i + 1), "<>"))
		(*i) += 2;
	else if (is_charset(*(s + *i), "<>"))
		less_or_greater_than(s, i, *(s + *i));
	if (!is_charset(*(s + *i), "<>&")
		|| (*(s + *i) == '&' && !is_charset(*(s + *i + 1), "<>")))
		(*i)++;
	skip_after_rdr(s, i);
}
