/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:34:57 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 14:14:10 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	skip_qmbt(char *str, int *i)
{
	char	qmbt;

	qmbt = *(str + *i);
	if (is_charset(qmbt, "\"'`"))
	{
		(*i)++;
		while (*(str + *i) && *(str + *i) != qmbt)
		{
			if (*(str + *i) == '\\')
			{
				(*i)++;
				if (*(str + *i) == qmbt)
					(*i)++;
			}
			else if (*(str + *i))
				(*i)++;
		}
	}
}

void	get_end_idx(char *s, int *i, char *charset, int flag)
{
	char	qmbt;

	while (*(s + *i) && !is_charset(*(s + *i), charset))
	{
		if (flag && ft_isdigit(*(s + *i)))
			break ;
		if (*(s + *i) != '\\')
		{
			qmbt = *(s + (*i)++);
			while (is_charset(qmbt, "\"'`")
				&& *(s + *i) && *(s + *i) != qmbt)
				(*i)++;
			if (is_charset(qmbt, "\"'`"))
				(*i)++;
		}
		else
		{
			(*i)++;
			if (is_charset(*(s + *i), "\\;|'\"`<>&"))
				(*i)++;
		}
	}
}

int	rdr_after_fd(char *s, int *i)
{
	while (ft_isdigit(*(s + *i)))
		(*i)++;
	if (check_valid_rdr_symbols(s, *i))
		return (1);
	return (0);
}

void	split_n_insert(t_cursor *cur, char **s, int start, int *i)
{
	t_cmds	*new;
	int		len;

	if (!start)
		return ;
	len = (int)ft_strlen(*s);
	cur->elem->cmd = ft_strndup(*s, start);
	new = ps_lst_init(ft_substr(*s, start, len - start));
	new->next = cur->elem->next;
	cur->elem->next = new;
	cur->elem = new;
	free(*s);
	*s = NULL;
	if (*i != len)
	{
		*s = new->cmd;
		*i = 0;
	}
}
