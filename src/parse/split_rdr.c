/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 21:31:30 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 22:18:44 by ghan             ###   ########.fr       */
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
	while (is_charset(*(s + *i), " \n\t"))
		(*i)++;
}

int	check_valid_rdr_symbols(char *s, int i)
{
	if (ft_strlen(s + i) >= 2
		&& *(s + i) == '&' && !is_charset(*(s + i + 1), "<>"))
		return (0);
	else if (is_charset(*(s + i), "<>") || (ft_strlen(s + i) >= 2
			&& *(s + i) == '&' && is_charset(*(s + i + 1), "<>")))
		return (1);
	return (0);
}

int	get_rdr_end_idx(char *s, int *i)
{
	if (*(s + *i) == '&' && !is_charset(*(s + *i + 1), "<>"))
	{
		(*i)++;
		while (*(s + *i) == '&')
			(*i)++;
		return (0);
	}
	if (*(s + *i) == '&' && is_charset(*(s + *i + 1), "<>"))
		(*i) += 2;
	else if (is_charset(*(s + *i), "<>"))
		less_or_greater_than(s, i, *(s + *i));
	if (*(s + *i))
		skip_after_rdr(s, i);
	return (1);
}
