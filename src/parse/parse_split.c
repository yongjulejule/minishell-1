/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 01:54:44 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 01:55:05 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	get_end_idx(char *s, int *i, char *charset)
{
	char	qmbt;

	while (*(s + *i) && !is_charset(*(s + *i), charset))
	{
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

static void	split_n_insert(t_cmds **cur, char **s, int start, int *i)
{
	t_cmds	*new;
	int		len;

	(*cur)->cmd = ft_strndup(*s, start);
	new = ps_lst_init(ft_substr(*s, start, *i - start));
	new->next = (*cur)->next;
	(*cur)->next = new;
	(*cur) = (*cur)->next;
	len = (int)ft_strlen(*s);
	free(*s);
	*s = NULL;
	if (*i != len)
	{
		*s = (*cur)->cmd;
		*i = 0;
	}
}

static int	rdr_after_fd(char *s, int *i)
{
	while (ft_isdigit(*(s + *i)))
		(*i)++;
	if (check_valid_rdr_symbols(s, *i))
		return (1);
	return (0);
}

static void	split_by_rdr(t_cmds **cur, int i)
{
	char	*s;
	int		start;

	s = (*cur)->cmd;
	while (s && *(s + i))
	{
		start = i;
		if (ft_isdigit(*(s + i)))
		{
			if (rdr_after_fd(s, &i))
			{
				get_rdr_end_idx(s, &i);
				split_n_insert(cur, &s, start, &i);
			}
			else
				get_end_idx(s, &i, "<>&");
		}
		if (!is_charset(*(s + i), "<>&"))
			get_end_idx(s, &i, "<>&");
		else if (is_charset(*(s + i), "<>&"))
		{
			get_rdr_end_idx(s, &i);
			split_n_insert(cur, &s, start, &i);
		}
	}
}

static void	split_by_pipe_sc(t_cmds **hd, char *s)
{
	int	start;
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (!is_charset(*(s + i), ";|"))
		{
			start = i;
			get_end_idx(s, &i, ";|");
			ps_lst_addback(hd, ps_lst_init(ft_substr(s, start, i - start)));
		}
		else if (*(s + i) != '\0')
		{
			if (*(s + i) == ';')
				ps_lst_addback(hd, ps_lst_init(ft_strdup(";")));
			else if (*(s + i) == '|')
				ps_lst_addback(hd, ps_lst_init(ft_strdup("|")));
			i++;
		}
	}
}

void	split_by_symbols(t_cmds **cmds_hd, char *one_ln)
{
	t_cmds	*elem;

	if (!one_ln)
		return ;
	if (*one_ln == '\0')
		ps_lst_addback(cmds_hd, ps_lst_init(ft_strdup("")));
	else
	{
		split_by_pipe_sc(cmds_hd, one_ln);
		free(one_ln);
		one_ln = NULL;
		elem = (*cmds_hd)->next;
		while (elem)
		{
			if (ft_strcmp(elem->cmd, ";") && ft_strcmp(elem->cmd, "|"))
				split_by_rdr(&elem, 0);
			elem = elem->next;
		}
	}
}
