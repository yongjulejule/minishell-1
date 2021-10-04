/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:15:16 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 16:12:21 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_one_str(char *str)
{
	if (!ft_strcmp(";", str))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
		return (0);
	}
	else if (!ft_strcmp("|", str))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	write_pp_sm_error(char *first, char *secnd)
{
	if (!ft_strcmp(";", first) && !ft_strcmp(";", secnd))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;;'",
			STDERR_FILENO);
	else if ((!ft_strcmp("", first) && !ft_strcmp(";", secnd))
		|| (!ft_strcmp(";", first) && !ft_strcmp("|", secnd)))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
	else if (!ft_strcmp("|", first) && !ft_strcmp("|", secnd))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `||'",
			STDERR_FILENO);
	else if ((!ft_strcmp("", first) && !ft_strcmp("|", secnd))
		|| (!ft_strcmp("|", first) && !ft_strcmp(";", secnd)))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
	else if (!ft_strcmp("|", first))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
	else if (!ft_strcmp(";", first))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
}

int	check_smcol_pipe_syntax(t_cmds *elem)
{
	int	i;

	i = 0;
	while (elem->next)
	{
		if ((!ft_strcmp(";", elem->cmd) && !ft_strcmp(";", elem->next->cmd))
			|| (!ft_strcmp("", elem->cmd) && !ft_strcmp(";", elem->next->cmd))
			|| (!ft_strcmp("|", elem->cmd) && !ft_strcmp("|", elem->next->cmd))
			|| (!ft_strcmp("", elem->cmd) && !ft_strcmp("|", elem->next->cmd))
			|| (!ft_strcmp(";", elem->cmd) && !ft_strcmp("|", elem->next->cmd))
			|| (!ft_strcmp("|", elem->cmd) && !ft_strcmp(";", elem->next->cmd))
			|| (!i
				&& (!ft_strcmp("|", elem->cmd) || !ft_strcmp(";", elem->cmd))))
		{
			write_pp_sm_error(elem->cmd, elem->next->cmd);
			return (0);
		}
		elem = elem->next;
		i++;
	}
	if (!i && !check_one_str(elem->cmd))
		return (0);
	return (1);
}

static void	write_cons_rdr_error(char *str)
{
	char	*to_free;
	int		len;

	len = 1;
	if ((*str == '>' && is_charset(*(str + 1), ">&"))
		|| (is_charset(*str, "<&") && is_charset(*(str + 1), "<>&")))
		len++;
	to_free = ft_strndup(str, len);
	ft_putstr_fd("🤣 esh: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(to_free, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free(to_free);
}

int	check_rdr_syntax(t_cmds *elem)
{
	char	*symbols[9];
	int		len;

	init_symbols(symbols);
	len = ps_lst_size(elem);
	if (is_strset(ps_lstlast(elem)->cmd, symbols)
		|| is_strset_end(ps_lstlast(elem)->cmd, symbols))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (0);
	}
	while (len > 1 && elem->next)
	{
		if ((is_strset(elem->cmd, symbols)
				|| is_strset_end(elem->cmd, symbols))
			&& check_valid_rdr_symbols(elem->next->cmd, 0))
		{
			write_cons_rdr_error(elem->next->cmd);
			return (0);
		}
		elem = elem->next;
	}
	return (1);
}
